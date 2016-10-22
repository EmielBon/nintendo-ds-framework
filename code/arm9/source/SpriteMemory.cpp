#include "SpriteMemory.h"
#include "Logging.h"
#include "VideoRamBank.h"
#include "MathFunctions.h"
#include <nds/arm9/video.h>

namespace Graphics
{
	using namespace std;
	using namespace Debug;

	//-------------------------------------------------------------------------------------------------
	SpriteMemory::SpriteMemory(bool isMain) : super(isMain, MemoryType::Memory_SPR)
	{
		
	}

	//-------------------------------------------------------------------------------------------------
	void SpriteMemory::Initialize()
	{
		if (IsMain())
		{
			InitializeSlots(2);

			Slots[0]->AddSupportedMapping(BankA, VRAM_A_MAIN_SPRITE_0x06400000);
			Slots[0]->AddSupportedMapping(BankB, VRAM_B_MAIN_SPRITE_0x06400000);
			Slots[0]->AddSupportedMapping(BankE, VRAM_E_MAIN_SPRITE);            // First half of slot 0
			Slots[0]->AddSupportedMapping(BankF, VRAM_F_MAIN_SPRITE_0x06400000); // 1st half, 1st part of slot 0
			Slots[0]->AddSupportedMapping(BankG, VRAM_G_MAIN_SPRITE_0x06400000); // 1st half, 1st part of slot 0

			Slots[1]->AddSupportedMapping(BankA, VRAM_A_MAIN_SPRITE_0x06420000);
			Slots[1]->AddSupportedMapping(BankB, VRAM_B_MAIN_SPRITE_0x06420000);
		}
		else
		{
			InitializeSlots(1);

			Slots[0]->AddSupportedMapping(BankD, VRAM_D_SUB_SPRITE);
			Slots[0]->AddSupportedMapping(BankI, VRAM_I_SUB_SPRITE);
		}
	}

	//-------------------------------------------------------------------------------------------------
	int SpriteMemory::Maximum() const
	{
		return IsMain() ? 0x40000 : 0x20000;
	}

	//-------------------------------------------------------------------------------------------------
	u16* SpriteMemory::TileBaseAddress() const
	{
		return IsMain() ? SPRITE_GFX : SPRITE_GFX_SUB;
	}

	Sprite SpriteMemory::AddSprite(const TiledImage &tiledImage)
	{
		Size size = tiledImage.Size;
		ObjShape objShape = ObjShapeForSize(size);
		ObjSize objSize = ObjSizeForSize(size);

		for (auto &tile : tiledImage.Tiles)
		{
			AddTile(tile);
		}

		return Sprite(tiledImage[0].Identifier, objShape, objSize);
	}

	//-------------------------------------------------------------------------------------------------
	ObjSize SpriteMemory::ObjSizeForSize(Size size)
	{
		ObjSize objSize = OBJSIZE_8;

		int majorSize = Math::Max(size.Width, size.Height);

		switch (majorSize)
		{
		case  8: objSize = OBJSIZE_8;  break;
		case 16: objSize = OBJSIZE_16; break;
		case 32: objSize = OBJSIZE_32; break;
		case 64: objSize = OBJSIZE_64; break;
		default: CRASH("Error: Invalid sprite size"); break;
		}

		return objSize;
	}

	//-------------------------------------------------------------------------------------------------
	ObjShape SpriteMemory::ObjShapeForSize(Size size)
	{
		ObjShape shape = OBJSHAPE_SQUARE;
		int width = size.Width;
		int height = size.Height;

		if (width > height)
			shape = OBJSHAPE_WIDE;
		if (width < height)
			shape = OBJSHAPE_TALL;

		return shape;
	}
}
