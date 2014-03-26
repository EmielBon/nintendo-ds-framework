#pragma once

#include "types.h"
#include "VideoRamBankNames.h"

namespace Graphics
{
	class VideoRamBank;
	
	class MemorySlot
	{
	public:

		// Empty Constructor
		MemorySlot();
		
		/// Constructor, assigns the parent Memory2D
		MemorySlot(Memory2D *memory, int index);

		///
		void AddSupportedMapping(BankName bank, int VRAMCRMappingValue);

		/// Returns whether this slot is not mapped to a VRAM bank
		bool IsFree() const;

		///
		VideoRamBank* GetBank() const;

		/// Binds this MemorySlot to the specified VRAM bank
		void SetVRAMBank(VideoRamBank *bank);

		///
		void Release();

		/// Returns this slot's index
		int GetIndex() const;

		/// Returns a reference to this MemorySlot's parent memory
		Memory2D& GetMemory() const;

		/// Returns whether this MemorySlot is compatible with the specified VRAM bank
		bool IsCompatible(const VideoRamBank& bank) const;

		///
		int GetVRAMControlRegisterMappingValue();

	public:

		Memory2D *memory;
		const int index;

		int compatibleBanks;
		VideoRamBank *vramBank;

		// Maps compatible VRAM bank's names to the corresponding VRAM control register mapping value for this slot
		TreeMap<BankName, int> supportedMappings;
	};

	//-------------------------------------------------------------------------------------------------
	inline MemorySlot::MemorySlot() : memory(NULL), index(-1), vramBank(NULL)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline MemorySlot::MemorySlot(Memory2D *m, int i) : memory(m), index(i), vramBank(NULL)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline bool MemorySlot::IsFree() const
	{
		return (vramBank == NULL);
	}

	//-------------------------------------------------------------------------------------------------
	inline int MemorySlot::GetIndex() const
	{
		return index;
	}

	//-------------------------------------------------------------------------------------------------
	inline Memory2D& MemorySlot::GetMemory() const
	{
		return *memory;
	}

	//-------------------------------------------------------------------------------------------------
	inline void MemorySlot::Release()
	{
		vramBank = NULL;
	}
}