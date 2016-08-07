#include "graphics/TextureMemory.h"
#include "graphics/Texture.h"
#include "graphics/VideoRamBank.h"
#include "debug/Debug.h"
#include <nds/arm9/video.h>

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	TextureMemory::TextureMemory(bool isMain) : super(isMain, MemoryType::Memory_TEX), nextAvailableAddress(NULL)
	{
		// Somehow the Initialize function is needed, initialization of the memory 
		// slots cannot be done in the constructor. It seems it has something to do 
		// with the pointer to this Memory2D object, which is stored in the memory 
		// slots, is corrupt or something when stored in the constructor.
	}

	//-------------------------------------------------------------------------------------------------
	void TextureMemory::Initialize()
	{
		// Todo: texture palette can probably have more slots, and other palette memory types can also expand. For now just 1 for testing texture palettes
		// Todo: If VRAM_E is mapped to texture or extended palette, it occupies more than 1 slot. Make this possible
		// Todo: Implement palette support. Only direct colored textures for now
		//PaletteMemory.Initialize(this);
		//PaletteMemory.AddSlot(BankE | BankF | BankG);

		if (IsMain())
		{
			InitializeSlots(4);

			Slots[0]->AddSupportedMapping(BankA, VRAM_A_TEXTURE_SLOT0);
			Slots[0]->AddSupportedMapping(BankB, VRAM_B_TEXTURE_SLOT0);
			Slots[0]->AddSupportedMapping(BankC, VRAM_C_TEXTURE_SLOT0);
			Slots[0]->AddSupportedMapping(BankD, VRAM_D_TEXTURE_SLOT0);

			Slots[1]->AddSupportedMapping(BankA, VRAM_A_TEXTURE_SLOT1);
			Slots[1]->AddSupportedMapping(BankB, VRAM_B_TEXTURE_SLOT1);
			Slots[1]->AddSupportedMapping(BankC, VRAM_C_TEXTURE_SLOT1);
			Slots[1]->AddSupportedMapping(BankD, VRAM_D_TEXTURE_SLOT1);

			Slots[2]->AddSupportedMapping(BankA, VRAM_A_TEXTURE_SLOT2);
			Slots[2]->AddSupportedMapping(BankB, VRAM_B_TEXTURE_SLOT2);
			Slots[2]->AddSupportedMapping(BankC, VRAM_C_TEXTURE_SLOT2);
			Slots[2]->AddSupportedMapping(BankD, VRAM_D_TEXTURE_SLOT2);

			Slots[3]->AddSupportedMapping(BankA, VRAM_A_TEXTURE_SLOT3);
			Slots[3]->AddSupportedMapping(BankB, VRAM_B_TEXTURE_SLOT3);
			Slots[3]->AddSupportedMapping(BankC, VRAM_C_TEXTURE_SLOT3);
			Slots[3]->AddSupportedMapping(BankD, VRAM_D_TEXTURE_SLOT3);

			// Todo: hack, only works if BankA is mapped to TextureMemory
			nextAvailableAddress = VRAM_A;
		}
	}

	//-------------------------------------------------------------------------------------------------
	int TextureMemory::Maximum() const
	{
		// Main engine can use 512kb (Bank A through D) for textures. Sub engine has no 3D, so no textures
		return (IsMain()) ? 0x80000 : 0; 
	}

	//-------------------------------------------------------------------------------------------------
	bool TextureMemory::HasTexture(Ptr<Texture> texture)
	{
		return (GetTextureAddress(texture) != NULL);
	}

	//-------------------------------------------------------------------------------------------------
	void TextureMemory::AddTexture(Ptr<Texture> texture)
	{
		ASSERT(texture != nullptr, "Null pointer to texture");

		if (HasTexture(texture))
			return;
		
		//PaletteMemory.AddPalette(texture->Palette, true);
		//ASSERT(PaletteMemory.HasPalette(texture->Palette), "Palette not in memory");

		CopyTextureToVRAM(texture);
	}

	//-------------------------------------------------------------------------------------------------
	u16* TextureMemory::GetTextureAddress(Ptr<Texture> texture)
	{
		ASSERT(texture != nullptr, "Error: Texture may not be null");

		if(TextureAddresses.find(texture) == TextureAddresses.end())
		{
			return NULL;
		}

		return TextureAddresses[texture];
	}

	//-------------------------------------------------------------------------------------------------
	void TextureMemory::CopyTextureToVRAM(Ptr<Texture> texture)
	{
		Reserve(texture->GetByteSize());
		
		auto mappedBanks = GetMappedBanks();

		// LCD mapping means the CPU can directly access the VRAM. 
		for(u32 i = 0; i < mappedBanks.size(); ++i)
			mappedBanks[i]->AssignToLCD();
		
		Replace(texture->Pixels, nextAvailableAddress);
		
		for(u32 i = 0; i < mappedBanks.size(); ++i)
			mappedBanks[i]->Restore();

		TextureAddresses[texture] = nextAvailableAddress;
		// Todo: not correct when some sort of compression is implemented
		nextAvailableAddress += texture->Pixels.size();
	}
}