#pragma once

#include "Memory2D.h"
#include "PaletteMemory.h"
#include "types.h"
#include "TilesManager.h"

namespace Graphics
{
	class TileMemory : public Memory2D
	{
	private:

		using super = Graphics::Memory2D;

	protected:

		TileMemory();

		TileMemory(bool isMain, u32 type);

		virtual int TileBase() const = 0;

		virtual u16* TileBaseAddress() const = 0;

	public:

		/// Add a single tile to VRAM
		void AddTile(u32 identifier);

		/// Add a single tile to VRAM, without checking if it is already in VRAM
		void AddTileUnsafe(u32 identifier);

		/// Add a complete tile set to VRAM
		void AddTiles(const Set<u32> &identifiers);

		///
		Ptr< List<byte> > OffsetPixelsForTile(const Tile &tile, int offset, bool transparent);

		///
		void RegisterVRAMIndexForTile(u32 identifier, u32 VRAMIndex);

		///
		bool TileInVRAM(u32 identifier) const;

		///
		u32 VRAMIndexForIdentifier(u32 identifier) const;

	public:

		Graphics::PaletteMemory PaletteMemory;
		int nextAvailableIndex;
		Dictionary<u32, u32> IdentifierToVRAMIndex;
	};

	//-------------------------------------------------------------------------------------------------
	inline TileMemory::TileMemory() : nextAvailableIndex(0)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline TileMemory::TileMemory(bool isMain, u32 type) : super(isMain, type), PaletteMemory(isMain, type | Memory_PAL), nextAvailableIndex(0)
	{
		
	}

	//-------------------------------------------------------------------------------------------------
	finline void TileMemory::AddTile(u32 identifier)
	{
		if (!TileInVRAM(identifier))
			AddTileUnsafe(identifier);
	}

	//-------------------------------------------------------------------------------------------------
	finline void TileMemory::RegisterVRAMIndexForTile( u32 identifier, u32 VRAMIndex )
	{
		IdentifierToVRAMIndex[identifier] = VRAMIndex;
	}

	//-------------------------------------------------------------------------------------------------
	finline bool TileMemory::TileInVRAM( u32 identifier ) const
	{
		return (IdentifierToVRAMIndex.find(identifier) != IdentifierToVRAMIndex.end());
	}

	//-------------------------------------------------------------------------------------------------
	finline u32 TileMemory::VRAMIndexForIdentifier( u32 identifier ) const
	{
		ASSERT(TileInVRAM(identifier), "Tile not in VRAM");
		return IdentifierToVRAMIndex.at(identifier);
	}
}