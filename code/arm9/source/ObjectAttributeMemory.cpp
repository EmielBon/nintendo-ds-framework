#include "ObjectAttributeMemory.h"
#include "GraphicsDevice.h"
#include "Logging.h"
#include "MathFunctions.h"
#include "Sprite.h"
#include "TileSet256.h"
#include "FixedHelper.h"
#include "SpriteResource.h"
#include "TilesManager.h"
#include <nds/dma.h>
#include <nds/arm9/cache.h>

namespace Graphics
{
	using namespace LLR;
	using namespace Math;
	using namespace Util;

	//-------------------------------------------------------------------------------------------------
	ObjectAttributeMemory::ObjectAttributeMemory(Graphics::GraphicsDevice *device) : DisplayMode(SpriteDisplayMode_1D_64), graphicsDevice(device), oam(NULL), location(NULL)
	{
		ASSERT(device != NULL, "Error: ObjectAttributeMemory initialized with NULL device");

		oam = new OAMTable();
		location = graphicsDevice->IsMain() ? OAM : OAM_SUB;

		Reset();
		Update();
	}

	//-------------------------------------------------------------------------------------------------
	void ObjectAttributeMemory::Update()
	{
		ASSERT(graphicsDevice != NULL && oam != NULL && location != NULL, "Error: OAM not initialized");

		ASSERT2(sprites.size() < 2, "Count " << sprites.size());

		for(u32 i = 0; i < sprites.size(); ++i)
		{
			auto& sprite        = *sprites[i];
			auto& oamSprite     = *oamSpriteMap[sprites[i]];
			SpriteEntry &oamObj = oam->oamBuffer[i];
			
			oamObj = oamSprite.OAMSpriteEntries[sprite.SubImageIndex];
			oamObj.rotationIndex = i;

			SpriteRotation &rotObj = oam->matrixBuffer[i];
			rotObj.hdx = FixedHelper::Tof16(fx8(1) / sprite.Scale);
			rotObj.hdy = 0;
			rotObj.vdx = 0;
			rotObj.vdy = FixedHelper::Tof16(fx8(1) / sprite.Scale);

			// Todo: Tighter coupling between sprite and oam sprite
			// Todo: Hacky
			/*SpriteEntry &oamObj = oam->oamBuffer[i];
			Sprite &sprite = *sprites[i];
			Sprite &oamSprite = *oamSpriteMap[sprites[i]];
			int tileCount = sprite.TileSet->Get8x8TilesPerTile();
			oamObj.gfxIndex = oamSprite.SubImages[sprite.SubImageIndex] * tileCount * GetSpriteTileStride(); // Klopt alleen als alle sprites even groot zijn
			oamObj.x = sprite.X;
			oamObj.y = sprite.Y;
			oamObj.isHidden = false;
			oamObj.isMosaic = false;
			oamObj.isRotateScale = true;
			oamObj.isSizeDouble = false;
			oamObj.size = sprite.size;
			oamObj.shape = sprite.shape;
			oamObj.priority = sprite.Priority;
			oamObj.colorMode = OBJCOLOR_256;*/
		}

		DC_FlushAll();
		dmaCopy( oam->oamBuffer, location, SPRITE_MAX * sizeof(SpriteEntry) );
		Reset();
	}

	//-------------------------------------------------------------------------------------------------
	void ObjectAttributeMemory::DrawSprite(Ptr<Sprite> sprite)
	{
		ASSERT(sprites.size() < SPRITE_MAX, "Error: Sprite limit reached");
		
		sprites.push_back(sprite);

		//if (oamSpriteMap.find(sprite) == oamSpriteMap.end())
		//{
			// Add the tiles for this sprite to sprite memory
			//ASSERT2(false, sprite->UniqueIndices.size());
			graphicsDevice->SpriteMemory.AddTiles(sprite->UniqueIndices);
			// Add the sprite to object attribute memory
			Ptr<SpriteResource> oamSprite = Convert(*sprite);
			oamSpriteMap[sprite] = oamSprite;
		//}
	}

	//-------------------------------------------------------------------------------------------------
	Ptr<SpriteResource> ObjectAttributeMemory::Convert(const Sprite &sprite) const
	{
		Ptr<SpriteResource> converted = New<SpriteResource>();

		for(u32 i = 0; i < sprite.SubImages.size(); ++i)
		{
			u32 tileIdentifier = sprite.SubImages[i].TileIdentifiers[0]; // Upper left tile is used for sprite indexing
			
			SpriteEntry entry;
			entry.gfxIndex = graphicsDevice->SpriteMemory.VRAMIndexForIdentifier(tileIdentifier);
			entry.x = sprite.X;
			entry.y = sprite.Y;
			entry.isHidden = false;
			entry.isMosaic = false;
			entry.isRotateScale = true;
			entry.isSizeDouble = false;
			entry.size = sprite.size;
			entry.shape = sprite.shape;
			entry.priority = sprite.Priority;
			entry.colorMode = OBJCOLOR_256;
			
			converted->OAMSpriteEntries.push_back(entry);
			//u32 &val = (*converted).SubImages[i];
			//auto vramIndex = tileIndexMap.find(val * TileSet->Get8x8TilesPerTile());

			//if (vramIndex != tileIndexMap.end())
			//	val = vramIndex->second / TileSet->Get8x8TilesPerTile();
		}

		return converted;
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
		ASSERT(oam != NULL, "Error: OAM not initialized");

		/*
		 * For all 128 sprites on the DS, disable and clear any attributes they 
		 * might have. This prevents any garbage from being displayed and gives 
		 * us a clean slate to work with.
		 */
		for (u32 i = 0; i < sprites.size(); ++i) 
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

		sprites.clear();
	}
}