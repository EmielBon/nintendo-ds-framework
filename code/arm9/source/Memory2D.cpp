#include "Memory2D.h"

#include "VideoRam.h"
#include "Debug.h"
#include <nds/bios.h>
#include <nds/dma.h>

namespace Graphics
{
	using namespace std;

	//-------------------------------------------------------------------------------------------------
	void Memory2D::InitializeSlots(int nrOfSlots)
	{
		ASSERT(Slots.size() == 0, "Error: Slots already initialized");

		for(int i = 0; i < nrOfSlots; ++i)
			AddSlot( New<MemorySlot>(this, i) );
	}

	//-------------------------------------------------------------------------------------------------
	bool Memory2D::Reserve(int size)
	{
		if (size <= 0)
			return true;

		// Add additional memory if needed
		if ( available < size && totalSize < Maximum() )
			Expand();

		if ( available >= size )
		{
			available -= size;
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------------------------------
	void Memory2D::Expand()
	{
		auto& banks = VideoRam::Banks;

		for(u32 i = 0; i < Slots.size(); ++i)
		{
			MemorySlot& slot = *Slots[i];

			if (!slot.IsFree()) {
				continue;
			}
			for(auto bank = banks.begin(); bank != banks.end(); ++bank)
			{
				if ( bank->IsFree() && slot.IsCompatible(*bank) )
				{
					AssignBankToSlot(bank->GetName(), i);
					return;
				}
			}
		}

		sassert(false, "Error: Memory expansion failed!");
	}

	//-------------------------------------------------------------------------------------------------
	bool Memory2D::Add(const void *source, void *location, int size)
	{
		ASSERT(location != NULL, "Error: Copy data to NULL");
		
		if (size <= 0)
			return true;
		
		// Add additional memory if needed
		if ( available < size && totalSize < Maximum() )
		{
			if (AutomaticExpansion) 
				Expand();
			else
				ASSERT(false, "Error: No more memory available");
		}
		
		ASSERT(available >= size, "Error: Memory expansion failed");

		Copy(source, location, size);
		available -= size;
		return true;
	}

	//-------------------------------------------------------------------------------------------------
	bool Memory2D::Replace(const void *source, void *location, int size)
	{
		if (location == NULL)
		{
			LOG_WARNING(": attempt to move data to NULL");
			return false;
		}

		// Todo: Assert size not < 0
		if (size <= 0)
			return true;

		// Add additional memory if needed
		if ( totalSize < size && totalSize < Maximum() )
			Reserve(size);

		if ( totalSize >= size )
		{
			Copy(source, location, size);
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------------------------------
	void Memory2D::Copy(const void *source, void *dest, int size)
	{
		// swiCopy wants its size in half-words (16 bits), but size is in bytes (8bit, quart-words), so /2
		// Kopieren kan NIET met dmaCopy, het duurt 2 cycles voor die start en dan gaat het ding wat gekopieerd moet worden wss al out of scope
		swiCopy(source, dest, size / 2);
		//dmaCopy(source, dest, size);
	}

	//-------------------------------------------------------------------------------------------------
	bool Memory2D::IsMain() const
	{
		ASSERT(engineType != EngineType::UNDEFINED, "Error: Memory2D not assigned to main or sub engine");
		return (engineType == EngineType::MAIN);
	}

	//-------------------------------------------------------------------------------------------------
	void Memory2D::InitializeWithSize(int size)
	{
		ASSERT(totalSize == 0, "Error: Memory already initialized or expanded");
		totalSize = size;
		available = totalSize;
	}

	//-------------------------------------------------------------------------------------------------
	void Memory2D::AssignBankToSlot(BankName bankName, u32 slotIndex)
	{
		ASSERT(slotIndex >= 0 && slotIndex < Slots.size(), "Error: Slot index out of bounds");
		
		auto slot = Slots[slotIndex];
		VideoRamBank &bank = VideoRam::GetBank(bankName);

		ASSERT(bank.IsFree(), "Error: Bank is not free"); 
		ASSERT(slot->IsCompatible(bank), "Error: Bank is not compatible with slot");

		slot->SetVRAMBank(&bank);
		bank.SetOwner(slot);
		bank.SetMapping(slot->GetVRAMControlRegisterMappingValue());

		totalSize += bank.GetSize();
		available += totalSize;
		LOG("Added " << bank.GetSize()/1024 << "kb to memory");
	}

	//-------------------------------------------------------------------------------------------------
	List<VideoRamBank*> Memory2D::GetMappedBanks()
	{
		List<VideoRamBank*> banks;

		for(u32 i = 0; i < Slots.size(); ++i)
		{
			auto slot = Slots[i];
			if (!slot->IsFree())
				banks.push_back(slot->GetBank());
		}

		return banks;
	}

}