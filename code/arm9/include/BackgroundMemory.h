#pragma once

#include "TileMemory.h"
#include "Map.h"
#include "types.h"

namespace Graphics
{
	class BackgroundMemory : public TileMemory
	{
	private:

		using super = Graphics::TileMemory;

	public:

		///
		BackgroundMemory(bool isMain);

		/// 
		void Initialize();

		/// Returns the maximum size of this memory, determined by the physical limit of the Nintendo DS 
		int Maximum() const;

		/// Returns the graphics base index of the first tile in background memory
		int TileBase() const;

		///
		u16* TileBaseAddress() const;

	protected:

		/// Returns a free map index
		int GetFreeIndex() const;

	public:

		static const u32  MAP_MEMORY_MAX = 0x10000;
		static const u32 TILE_MEMORY_MAX = 0x40000; // Todo: Klopt dit wel?
		static const int       MAP_COUNT = 8;
		
		Array<Map, 8> Maps;
	};

	//-------------------------------------------------------------------------------------------------
	inline int BackgroundMemory::TileBase() const
	{
		// One 16kb tile base equals eight 2kb map bases (2kb = 1 32x32 map)
		//return mapLimit / 8;
		return 1;
	}

	//-------------------------------------------------------------------------------------------------
	inline int BackgroundMemory::Maximum() const
	{
		return IsMain() ? 0x80000 : 0x20000;
	}
}