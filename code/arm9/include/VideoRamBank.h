#pragma once

#include "types.h"
#include "VideoRamBankNames.h"
#include "MemoryTypes.h"

/*

All VRAM (and Palette, and OAM) can be written to only in 16bit and 32bit units (STRH, STR opcodes), 8bit writes are ignored (by STRB opcode)

*/
namespace Graphics
{
	class MemorySlot;

	class VideoRamBank
	{
	public:

		/// Empty Constructor
		VideoRamBank();

		/// Constructor
		VideoRamBank(BankName name, vu8* controlRegister, u16* location, int size);

		///
		void Release();

		/// Assign this bank to the specified slot
		void SetOwner(Ptr<MemorySlot> slot);

		/// Returns whether this VRAMBank is not mapped to a MemorySlot
		bool IsFree() const;

		/// Returns this VRAMBank's size in bytes
		int GetSize() const;

		/// Returns this VRAMBank's name
		BankName GetName() const;

		///
		Ptr<MemorySlot> GetOwner() const;

		///
		bool IsInitialized() const;

		/// Unmaps this bank. Allows for direct CPU write access to this bank, which is needed for writing texture data to TextureMemory. Restore re-maps this bank to its previous configuration
		void AssignToLCD();

		/// Re-maps this bank to its previous configuration after a call to AssignToLCD();
		void Restore();

		///
		void SetMapping(int VRAMCRMappingValue);

	private:

		///
		void SetStatus(int status);

	private:

		BankName        name;
		int             size;
		Ptr<MemorySlot> owner;
		vu8*            controlRegister;
		u16*            location;
		int			    oldVRAMCRMappingValue;
	};

	//-------------------------------------------------------------------------------------------------
	inline VideoRamBank::VideoRamBank() 
		: name(Bank0), size(0), controlRegister(NULL), location(NULL), oldVRAMCRMappingValue(0)
	{
	}

	//-------------------------------------------------------------------------------------------------
	inline bool VideoRamBank::IsFree() const
	{
		return owner == NULL;
	}

	//-------------------------------------------------------------------------------------------------
	inline int VideoRamBank::GetSize() const
	{
		return size;
	}

	//-------------------------------------------------------------------------------------------------
	inline BankName VideoRamBank::GetName() const
	{
		return name;
	}

	//-------------------------------------------------------------------------------------------------
	inline Ptr<MemorySlot> VideoRamBank::GetOwner() const
	{
		return owner;
	}

	//-------------------------------------------------------------------------------------------------
	inline bool VideoRamBank::IsInitialized() const
	{
		return name != Bank0;
	}

	//-------------------------------------------------------------------------------------------------
	inline void VideoRamBank::SetStatus(int status)
	{
		*controlRegister = status;
	}
}