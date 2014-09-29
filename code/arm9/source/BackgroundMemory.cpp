#include "BackgroundMemory.h"

#include "VideoRamBank.h"
#include "TiledBackground.h"
#include "Logging.h"
#include "SetHelper.h"
#include <nds/arm9/background.h>

namespace Graphics
{
	using namespace Util;
	using namespace Debug;

	//-------------------------------------------------------------------------------------------------
	BackgroundMemory::BackgroundMemory(bool isMain) : super(isMain, MemoryType::Memory_BG)
	{
		// Somehow the Initialize function is needed, initialization of the memory 
		// slots cannot be done in the constructor. It seems it has something to do 
		// with the pointer to this Memory2D object, which is stored in the memory 
		// slots, is corrupt or something when stored in the constructor.

		// Edit 7-10-2013: Or maybe it has something to do with the fact that the 
		// BackgroundMemory is initialized twice when done in the constructor, due 
		// to the fact that it is stored by value in the GraphicsDevice and again 
		// assigned to later
 	}

	void BackgroundMemory::Initialize()
	{
		if (IsMain())
		{
			InitializeSlots(4);

			Slots[0]->AddSupportedMapping(BankA, VRAM_A_MAIN_BG_0x06000000);
			Slots[0]->AddSupportedMapping(BankB, VRAM_B_MAIN_BG_0x06000000);
			Slots[0]->AddSupportedMapping(BankC, VRAM_C_MAIN_BG_0x06000000);
			Slots[0]->AddSupportedMapping(BankD, VRAM_D_MAIN_BG_0x06000000);
			Slots[0]->AddSupportedMapping(BankE, VRAM_E_MAIN_BG);            // First half of slot 0
			Slots[0]->AddSupportedMapping(BankF, VRAM_F_MAIN_BG_0x06000000); // 1st half, 1st part of slot 0
			Slots[0]->AddSupportedMapping(BankG, VRAM_G_MAIN_BG_0x06000000); // 1st half, 1st part of slot 0

			Slots[1]->AddSupportedMapping(BankA, VRAM_A_MAIN_BG_0x06020000);
			Slots[1]->AddSupportedMapping(BankB, VRAM_B_MAIN_BG_0x06020000);
			Slots[1]->AddSupportedMapping(BankC, VRAM_C_MAIN_BG_0x06020000);
			Slots[1]->AddSupportedMapping(BankD, VRAM_D_MAIN_BG_0x06020000);

			Slots[2]->AddSupportedMapping(BankA, VRAM_A_MAIN_BG_0x06040000);
			Slots[2]->AddSupportedMapping(BankB, VRAM_B_MAIN_BG_0x06040000);
			Slots[2]->AddSupportedMapping(BankC, VRAM_C_MAIN_BG_0x06040000);
			Slots[2]->AddSupportedMapping(BankD, VRAM_D_MAIN_BG_0x06040000);

			Slots[3]->AddSupportedMapping(BankA, VRAM_A_MAIN_BG_0x06060000);
			Slots[3]->AddSupportedMapping(BankB, VRAM_B_MAIN_BG_0x06060000);
			Slots[3]->AddSupportedMapping(BankC, VRAM_C_MAIN_BG_0x06060000);
			Slots[3]->AddSupportedMapping(BankD, VRAM_D_MAIN_BG_0x06060000);
		}
		else
		{
			InitializeSlots(1);

			Slots[0]->AddSupportedMapping(BankC, VRAM_C_SUB_BG_0x06200000);
			Slots[0]->AddSupportedMapping(BankH, VRAM_H_SUB_BG);            // 1st 2 parts of slot 0
			Slots[0]->AddSupportedMapping(BankI, VRAM_I_SUB_BG_0x06208000); // 3rd part of slot 0
		}

		for(u32 i = 0; i < Maps.size(); ++i)
		{
			Maps[i] = New<Map>(this, i);
		}
	}

	//-------------------------------------------------------------------------------------------------
	u16* BackgroundMemory::TileBaseAddress() const
	{
		int tileOffset = TileBase();
		return IsMain() ? BG_TILE_RAM(tileOffset) : BG_TILE_RAM_SUB(tileOffset);
	}
}