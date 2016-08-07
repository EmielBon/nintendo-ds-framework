#include "graphics/MemorySlot.h"
#include "graphics/VideoRamBank.h"
#include "debug/Debug.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	void MemorySlot::AddSupportedMapping(BankName bank, int VRAMCRMappingValue)
	{
		supportedMappings[bank] = VRAMCRMappingValue;
	}

	//-------------------------------------------------------------------------------------------------
	bool MemorySlot::IsCompatible(const VideoRamBank& bank) const
	{
		return (supportedMappings.count(bank.GetName()) == 1);
	}

	//-------------------------------------------------------------------------------------------------
	VideoRamBank* MemorySlot::GetBank() const
	{
		return vramBank;
	}

	//-------------------------------------------------------------------------------------------------
	void MemorySlot::SetVRAMBank(VideoRamBank *bank)
	{
		ASSERT(IsCompatible(*bank), "Error: Cannot bind slot to incompatible bank");

		vramBank = bank;
	}

	//-------------------------------------------------------------------------------------------------
	int MemorySlot::GetVRAMControlRegisterMappingValue()
	{
		ASSERT(vramBank != NULL, "Error: Request to give VRAM control register value for a slot without an assingned VRAM bank");

		return supportedMappings[vramBank->GetName()];
	}
}