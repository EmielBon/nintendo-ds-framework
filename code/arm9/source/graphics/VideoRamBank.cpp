#include "VideoRamBank.h"

#include "GraphicsDevice.h"
#include "Memory2D.h"
#include "MemorySlot.h"
#include "Logging.h"
#include "Debug.h"

#include <nds/arm9/background.h>

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	VideoRamBank::VideoRamBank(BankName n, vu8* cr, u16* loc, int size) 
		: name(n), size(size), controlRegister(cr), location(loc), oldVRAMCRMappingValue(0)
	{
		// Responsibility for these supported mappings now lies with the specific memory classes and memory slots.
		// However, this part of the code stays here (commented out) as a guide for the supported mappings for as long as not all mappings are fully supported

		/*if (name == BankA)
		{
			// Background memory
			AddSupportedMapping(true, Memory_BG, 0, VRAM_A_MAIN_BG_0x06000000);
			AddSupportedMapping(true, Memory_BG, 1, VRAM_A_MAIN_BG_0x06020000);
			AddSupportedMapping(true, Memory_BG, 2, VRAM_A_MAIN_BG_0x06040000);
			AddSupportedMapping(true, Memory_BG, 3, VRAM_A_MAIN_BG_0x06060000);
			// Sprite memory
			AddSupportedMapping(true, Memory_SPR, 0, VRAM_A_MAIN_SPRITE_0x06400000);
			AddSupportedMapping(true, Memory_SPR, 1, VRAM_A_MAIN_SPRITE_0x06420000);
			// Texture memory
			AddSupportedMapping(true, Memory_TEX, 0, VRAM_A_TEXTURE_SLOT0);
			AddSupportedMapping(true, Memory_TEX, 1, VRAM_A_TEXTURE_SLOT1);
			AddSupportedMapping(true, Memory_TEX, 2, VRAM_A_TEXTURE_SLOT2);
			AddSupportedMapping(true, Memory_TEX, 3, VRAM_A_TEXTURE_SLOT3);
		}
		else if (name == BankB)
		{
			// Background memory
			AddSupportedMapping(true, Memory_BG, 0, VRAM_B_MAIN_BG_0x06000000);
			AddSupportedMapping(true, Memory_BG, 1, VRAM_B_MAIN_BG_0x06020000);
			AddSupportedMapping(true, Memory_BG, 2, VRAM_B_MAIN_BG_0x06040000);
			AddSupportedMapping(true, Memory_BG, 3, VRAM_B_MAIN_BG_0x06060000);
			// Sprite memory
			AddSupportedMapping(true, Memory_SPR, 0, VRAM_B_MAIN_SPRITE_0x06400000);
			AddSupportedMapping(true, Memory_SPR, 1, VRAM_B_MAIN_SPRITE_0x06420000);
			// Texture memory
			AddSupportedMapping(true, Memory_TEX, 0, VRAM_B_TEXTURE_SLOT0);
			AddSupportedMapping(true, Memory_TEX, 1, VRAM_B_TEXTURE_SLOT1);
			AddSupportedMapping(true, Memory_TEX, 2, VRAM_B_TEXTURE_SLOT2);
			AddSupportedMapping(true, Memory_TEX, 3, VRAM_B_TEXTURE_SLOT3);
		}
		else if (name == BankC)
		{
			// Background memory
			AddSupportedMapping(true, Memory_BG, 0, VRAM_C_MAIN_BG_0x06000000);
			AddSupportedMapping(true, Memory_BG, 1, VRAM_C_MAIN_BG_0x06020000);
			AddSupportedMapping(true, Memory_BG, 2, VRAM_C_MAIN_BG_0x06040000);
			AddSupportedMapping(true, Memory_BG, 3, VRAM_C_MAIN_BG_0x06060000);
			AddSupportedMapping(false, Memory_BG, 0, VRAM_C_SUB_BG_0x06200000);
			// ARM7 workram
			// Todo: implement
			//AddMapping(Memory_ARM7WRAM, 0, VRAM_C_ARM7_0x06000000);
			//AddMapping(Memory_ARM7WRAM, 1, VRAM_C_ARM7_0x06020000);
			// Texture memory
			AddSupportedMapping(true, Memory_TEX, 0, VRAM_C_TEXTURE_SLOT0);
			AddSupportedMapping(true, Memory_TEX, 1, VRAM_C_TEXTURE_SLOT1);
			AddSupportedMapping(true, Memory_TEX, 2, VRAM_C_TEXTURE_SLOT2);
			AddSupportedMapping(true, Memory_TEX, 3, VRAM_C_TEXTURE_SLOT3);
		}
		else if (name == BankD)
		{
			// Background memory
			AddSupportedMapping(true, Memory_BG, 0, VRAM_D_MAIN_BG_0x06000000);
			AddSupportedMapping(true, Memory_BG, 1, VRAM_D_MAIN_BG_0x06020000);
			AddSupportedMapping(true, Memory_BG, 2, VRAM_D_MAIN_BG_0x06040000);
			AddSupportedMapping(true, Memory_BG, 3, VRAM_D_MAIN_BG_0x06060000);
			// ARM7 workram
			// Todo: implement
			//AddMapping(Memory_ARM7WRAM, 0, VRAM_D_ARM7_0x06000000);
			//AddMapping(Memory_ARM7WRAM, 1, VRAM_D_ARM7_0x06020000);
			// Sprite memory
			AddSupportedMapping(false, Memory_SPR, 0, VRAM_D_SUB_SPRITE);
			// Texture memory
			AddSupportedMapping(true, Memory_TEX, 0, VRAM_D_TEXTURE_SLOT0);
			AddSupportedMapping(true, Memory_TEX, 1, VRAM_D_TEXTURE_SLOT1);
			AddSupportedMapping(true, Memory_TEX, 2, VRAM_D_TEXTURE_SLOT2);
			AddSupportedMapping(true, Memory_TEX, 3, VRAM_D_TEXTURE_SLOT3);
		}
		else if (name == BankE)
		{
			// Background memory
			AddSupportedMapping(true, Memory_BG, 0, VRAM_E_MAIN_BG); // First half of slot 0
			// Sprite memory
			AddSupportedMapping(true, Memory_SPR, 0, VRAM_E_MAIN_SPRITE); // First half of slot 0
			// Texture palette
			AddSupportedMapping(true, Memory_TEXPAL, 0, VRAM_E_TEX_PALETTE); // Slot 0 - 3 Todo: maps 4 slots, add support
			// Background ext palette
			AddSupportedMapping(true, Memory_BGPAL, 0, VRAM_E_BG_EXT_PALETTE);
		}
		else if (name == BankF)
		{
			// Background memory
			AddSupportedMapping(true, Memory_BG, 0, VRAM_F_MAIN_BG_0x06000000); // 1st half, 1st part of slot 0
			//AddMapping(true, Memory_BG, 0, VRAM_F_MAIN_BG_0x06004000); // 1st half, 2nd part of slot 0
			//AddMapping(true, Memory_BG, 0, VRAM_F_MAIN_BG_0x06010000); // 2nd half, 1st part of slot 0
			//AddMapping(true, Memory_BG, 0, VRAM_F_MAIN_BG_0x06014000); // 2nd half, 2nd part of slot 0
			// Sprite memory
			AddSupportedMapping(true, Memory_SPR, 0, VRAM_F_MAIN_SPRITE_0x06400000); // 1st half, 1st part of slot 0
			//AddMapping(true, Memory_SPR, 0, VRAM_F_MAIN_SPRITE_0x06404000); // 1st half, 2nd part of slot 0
			//AddMapping(true, Memory_SPR, 0, VRAM_F_MAIN_SPRITE_0x06410000); // 2nd half, 1st part of slot 0
			//AddMapping(true, Memory_SPR, 0, VRAM_F_MAIN_SPRITE_0x06414000); // 2nd half, 2nd part of slot 0
			// Texture palette
			AddSupportedMapping(true, Memory_TEXPAL, 0, VRAM_F_TEX_PALETTE_SLOT0);
			AddSupportedMapping(true, Memory_TEXPAL, 1, VRAM_F_TEX_PALETTE_SLOT1);
			AddSupportedMapping(true, Memory_TEXPAL, 4, VRAM_F_TEX_PALETTE_SLOT4);
			AddSupportedMapping(true, Memory_TEXPAL, 5, VRAM_F_TEX_PALETTE_SLOT5);
			// Background ext palette
			AddSupportedMapping(true, Memory_BGPAL, 0, VRAM_F_BG_EXT_PALETTE_SLOT01); // Todo: maps 2 slots, add support
			AddSupportedMapping(true, Memory_BGPAL, 2, VRAM_F_BG_EXT_PALETTE_SLOT23); // Todo: maps 2 slots, add support
			// Sprite ext palette
			AddSupportedMapping(true, Memory_SPRPAL, 0, VRAM_F_SPRITE_EXT_PALETTE);
		}
		else if (name == BankG)
		{
			// Background memory
			AddSupportedMapping(true, Memory_BG, 0, VRAM_G_MAIN_BG_0x06000000); // 1st half, 1st part of slot 0
			//AddMapping(true, Memory_BG, 0, VRAM_G_MAIN_BG_0x06004000); // 1st half, 2nd part of slot 0
			//AddMapping(true, Memory_BG, 0, VRAM_G_MAIN_BG_0x06010000); // 2nd half, 1st part of slot 0
			//AddMapping(true, Memory_BG, 0, VRAM_G_MAIN_BG_0x06014000); // 2nd half, 2nd part of slot 0
			// Sprite memory
			AddSupportedMapping(true, Memory_SPR, 0, VRAM_G_MAIN_SPRITE_0x06400000); // 1st half, 1st part of slot 0
			//AddMapping(true, Memory_SPR, 0, VRAM_G_MAIN_SPRITE_0x06404000); // 1st half, 2nd part of slot 0
			//AddMapping(true, Memory_SPR, 0, VRAM_G_MAIN_SPRITE_0x06410000); // 2nd half, 1st part of slot 0
			//AddMapping(true, Memory_SPR, 0, VRAM_G_MAIN_SPRITE_0x06414000); // 2nd half, 2nd part of slot 0
			// Texture palette
			AddSupportedMapping(true, Memory_TEXPAL, 0, VRAM_G_TEX_PALETTE_SLOT0);
			AddSupportedMapping(true, Memory_TEXPAL, 1, VRAM_G_TEX_PALETTE_SLOT1);
			AddSupportedMapping(true, Memory_TEXPAL, 4, VRAM_G_TEX_PALETTE_SLOT4);
			AddSupportedMapping(true, Memory_TEXPAL, 5, VRAM_G_TEX_PALETTE_SLOT5);
			// Background ext palette
			AddSupportedMapping(true, Memory_BGPAL, 0, VRAM_G_BG_EXT_PALETTE_SLOT01); // Todo: maps 2 slots, add support
			AddSupportedMapping(true, Memory_BGPAL, 2, VRAM_G_BG_EXT_PALETTE_SLOT23); // Todo: maps 2 slots, add support
			// Sprite ext palette
			AddSupportedMapping(true, Memory_SPRPAL, 0, VRAM_G_SPRITE_EXT_PALETTE);
		}
		else if (name == BankH)
		{
			// Background memory
			AddSupportedMapping(false, Memory_BG, 0, VRAM_H_SUB_BG); // 1st 2 parts of slot 0
			// Background ext palette
			AddSupportedMapping(false, Memory_BGPAL, 0, VRAM_H_SUB_BG_EXT_PALETTE);
		}
		else if (name == BankI)
		{
			// Background memory
			//AddSupportedMapping(false, Memory_BG, 0, VRAM_I_SUB_BG_0x06208000); // 3rd part of slot 0
			// Sprite memory
			AddSupportedMapping(false, Memory_SPR, 0, VRAM_I_SUB_SPRITE);
			// Sprite ext palette
			AddSupportedMapping(false, Memory_SPRPAL, 0, VRAM_I_SUB_SPRITE_EXT_PALETTE);
		}*/
	}

	//-------------------------------------------------------------------------------------------------
	void VideoRamBank::Release()
	{
		if (owner) 
			owner->Release();

		owner = nullptr;

		AssignToLCD();
	}

	//-------------------------------------------------------------------------------------------------
	void VideoRamBank::SetOwner( Ptr<MemorySlot> slot )
	{
		// Todo: Needs optimization in the sense that MAIN BG can map lots of banks, 
		//       but takes BankC, the biggest bank available to SUB BG, as the third 
		//       (or second, if sprite memory is allocated) choice for BGMEM expansion 

		ASSERT(IsInitialized(),          "Error: Uninitialized VRAM bank");
		ASSERT(slot->IsCompatible(*this), "Error: This VRAM bank cannot be assigned to the specified slot");
		
		owner = slot;
	}

	//-------------------------------------------------------------------------------------------------
	void VideoRamBank::AssignToLCD()
	{
		oldVRAMCRMappingValue = *controlRegister;
		SetMapping(0);
	}

	//-------------------------------------------------------------------------------------------------
	void VideoRamBank::Restore()
	{
		SetMapping(oldVRAMCRMappingValue);
	}

	//-------------------------------------------------------------------------------------------------
	void VideoRamBank::SetMapping(int VRAMCRMappingValue)
	{
		// Store the value for AssignToLCD and Restore
		SetStatus(VRAM_ENABLE | VRAMCRMappingValue);
	}
}