#include "ObjectAttributeMemory.h"
#include "GraphicsDevice.h"
#include "Logging.h"
#include "MathFunctions.h"
#include "Sprite.h"
#include "FixedHelper.h"
#include "SpriteMemory.h"
#include <nds/dma.h>
#include <nds/arm9/cache.h>

namespace Graphics
{
	using namespace Math;
	using namespace Util;

	//-------------------------------------------------------------------------------------------------
	ObjectAttributeMemory::ObjectAttributeMemory(Graphics::GraphicsDevice *device) : DisplayMode(SpriteDisplayMode_1D_64), graphicsDevice(device), oam(NULL), location(NULL), spriteCount(0)
	{
		sassert(device, "Error: ObjectAttributeMemory initialized with NULL device");

		oam = new OAMTable();
		location = graphicsDevice->IsMain() ? OAM : OAM_SUB;

		Reset();
		Update();
	}

	//-------------------------------------------------------------------------------------------------
	void ObjectAttributeMemory::Update()
	{
		sassert(graphicsDevice && oam && location , "Error: OAM not initialized");

		DC_FlushAll();
		dmaCopy( oam->oamBuffer, location, SPRITE_MAX * sizeof(SpriteEntry) );
		Reset();
	}

	//-------------------------------------------------------------------------------------------------
	void ObjectAttributeMemory::DrawSprite(const Sprite &sprite, fx12 x, fx12 y, fx12 imageIndex, fx8 horizontalScale, fx8 verticalScale)
	{
		int subImageIndex = (int)imageIndex % sprite.SubImages.size();
		u32 tileIdentifier = sprite.SubImages[subImageIndex].Tiles[0]->Identifier; // Upper left tile is used for sprite indexing

		auto &entry = oam->oamBuffer[spriteCount];
		entry.gfxIndex = graphicsDevice->SpriteMemory->VRAMIndexForTile(tileIdentifier);
		entry.x = (int)Math::Round(x);
		entry.y = (int)Math::Round(y);
		entry.isHidden = false;
		entry.isMosaic = false;
		entry.isRotateScale = true;
		entry.isSizeDouble = false;
		entry.size = sprite.size;
		entry.shape = sprite.shape;
		entry.priority = sprite.Priority;
		entry.colorMode = OBJCOLOR_256;
		entry.rotationIndex = spriteCount;

		SpriteRotation &rotObj = oam->matrixBuffer[spriteCount];
		rotObj.hdx = FixedHelper::Tof16(fx8(1) / horizontalScale);
		rotObj.hdy = 0;
		rotObj.vdx = 0;
		rotObj.vdy = FixedHelper::Tof16(fx8(1) / verticalScale);

		spriteCount++;
	}

	//-------------------------------------------------------------------------------------------------
	int ObjectAttributeMemory::GetSpriteTileStride()
	{
		switch (DisplayMode)
		{
		//case SpriteDisplayMode_1D_32:  return 2; // Indexing per halve 8x8 tile (currently unsupported), max 512 8x8 tiles
		case SpriteDisplayMode_1D_64: return 1; // Indexing per hele 8x8 tile, max 1024 8x8 tiles
		//case SpriteDisplayMode_1D_128: return 0.5; // Indexing per 2 8x8 tiles (currently unsupported), gaten ontstaan na elke 8x8 tile
		//case SpriteDisplayMode_1D_256: return 0.25; // Indexing per 4 8x8 tiles (currently unsupported)
		default: return 1;
		}
	}

	//-------------------------------------------------------------------------------------------------
	void ObjectAttributeMemory::Reset()
	{
		sassert(oam, "Error: OAM not initialized");

		/*
		 * For all 128 sprites on the DS, disable and clear any attributes they 
		 * might have. This prevents any garbage from being displayed and gives 
		 * us a clean slate to work with.
		 */
		for (int i = 0; i < spriteCount; ++i)
		{
			oam->oamBuffer[i].attribute[0] = ATTR0_DISABLED;
			oam->oamBuffer[i].attribute[1] = 0;
			oam->oamBuffer[i].attribute[2] = 0;
		}
		/* 
		 * If you look carefully, you'll see this is that affine transformation
		 * matrix again. We initialize it to the identity matrix, as we did
		 * with backgrounds
		 */
		for (u32 i = 0; i < SPRITE_MAX_AFFINE; ++i)
		{
			oam->matrixBuffer[i].hdx = FixedHelper::Tof16( fx8(1) );
			oam->matrixBuffer[i].hdy = FixedHelper::Tof16( fx8(0) );
			oam->matrixBuffer[i].vdx = FixedHelper::Tof16( fx8(0) );
			oam->matrixBuffer[i].vdy = FixedHelper::Tof16( fx8(1) );
		}

		spriteCount = 0;
	}
}
