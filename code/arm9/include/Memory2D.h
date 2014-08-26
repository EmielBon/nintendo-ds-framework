#pragma once

#include "types.h"
#include "MemoryTypes.h" // Included here because every Memory2D subclass needs to specify its type
#include "MemorySlot.h"
#include "Assert.h"

namespace Graphics
{
	enum EngineType
	{
		UNDEFINED = -1,
		MAIN = 0,
		SUB = 1,
	};

	class Memory2D
	{
	public:

		/// 
		Memory2D() = delete;

		/// Constructor, creates an empty Memory2D object that is unusable until a call to Init()
		Memory2D(bool isMain, u32 type);

	protected:

		///
		bool Reserve(int size);

		/// Expand the memory by mapping a compatible VRAM bank to the next empty slot, if possible. Returns whether successful
		void Expand();

		///
		bool Add(const void *source, void *location, int size);

		// Todo: These Add and Replace functions do not really work as expected!

		/// Add a Resource to the Nintendo DS's internal memory
		template<class T>
		bool Add(const List<T>& resource, void* location);

		///
		template<class T>
		bool Replace(const List<T>& resource, void* location);

		/// Replace a resource in the Nintendo DS's internal memory
		bool Replace(const void *source, void *location, int size);

		/// Copy data to a location
		/// Todo: Can copy to any location using this function, is it good to have it here? Shouldn't this memory know something about itself?
		void Copy(const void *resource, void *location, int size);

		/// 
		void InitializeSlots(int nrOfSlots);

		/// Add a slot to this Memory2D object's list of usable slots
		void AddSlot(Ptr<MemorySlot> slot);

		/// Gets the byte size of the given resource
		template<class T>
		int GetByteSize(const List<T> &resource) const;

		/// Sets the size of this Memory2D. Only use if memory is mapped to this object prior to expanding it, like for PaletteMemory which has reserved palette RAM
		void InitializeWithSize(int totalSize);

	public:

		/// Returns this Memory2D object's maximum size, meant to be specified by the subclass that extends this class
		virtual int Maximum() const = 0;

		/// Returns this Memory2D object's type, i.e. the kind of data it contains
		u32 GetType() const;

		/// 
		int GetSize() const;

		/// Returns whether this Memory2D belongs to the main engine. Throws an exception if it is not yet initialized
		bool IsMain() const;

		///
		void AssignBankToSlot(BankName bankName, u32 slotIndex);

		/// Get all banks mapped to MemorySlots belonging to this Memory2D object
		List<VideoRamBank*> GetMappedBanks();

	private:

		u32 type;
		EngineType engineType;
		int totalSize, available;

	protected:

		List<Ptr<MemorySlot>> Slots;

	public:

		bool AutomaticExpansion;
	};

	//-------------------------------------------------------------------------------------------------
	inline Memory2D::Memory2D(bool isMain, u32 type) : type(type), totalSize(0), available(0), AutomaticExpansion(true)
	{
		engineType = (isMain) ? EngineType::MAIN : EngineType::SUB;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline bool Memory2D::Add(const List<T> &resource, void *location)
	{
		return Add(resource.data(), location, GetByteSize(resource));
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline bool Memory2D::Replace(const List<T> &resource, void *location)
	{
		return Replace(resource.data(), location, GetByteSize(resource));
	}

	//-------------------------------------------------------------------------------------------------
	inline void Memory2D::AddSlot(Ptr<MemorySlot> slot)
	{
		Slots.push_back(slot);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline int Memory2D::GetByteSize(const List<T> &resource) const
	{
		return resource.size() * sizeof(T);
	}

	//-------------------------------------------------------------------------------------------------
	inline int Memory2D::GetSize() const
	{
		return totalSize;
	}

	//-------------------------------------------------------------------------------------------------
	inline u32 Memory2D::GetType() const
	{
		//ASSERT(type != MemoryType::Memory_NONE, "dsds");

		return type;
	}
}