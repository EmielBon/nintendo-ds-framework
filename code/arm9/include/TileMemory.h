#pragma once

#include "Memory2D.h"
#include "types.h"

namespace Graphics
{
	class TileMemory : public Memory2D
	{
	private:

		using super = Graphics::Memory2D;

	protected:

		TileMemory(bool isMain, u32 type);

		virtual int TileBase() const = 0;

		virtual u16* TileBaseAddress() const = 0;

	public:

		/// Add a single tile to VRAM, returns the VRAM index it was copied to
		// todo: remove dynamicPaletteStartIndex argument
		u32 AddTile(const Tile &tile, int dynamicPaletteStartIndex = -1);

		/// todo: rename
		Ptr< List<byte> > OffsetPixelsForTile(const Tile &tile);

		/// todo: remove
		Ptr< List<byte> > OffsetPixelsForTile(const Tile &tile, int offset);

		///
		void RegisterVRAMIndexForTile(u32 identifier, u32 VRAMIndex);

		///
		bool TileInVRAM(u32 identifier) const;

		///
		int VRAMIndexForTile(u32 identifier) const;

	public:

		Ptr<Graphics::PaletteMemory> PaletteMemory;
		int nextAvailableIndex;
		Dictionary<u32, u32> IdentifierToVRAMIndex;
	};

	//-------------------------------------------------------------------------------------------------
	finline void TileMemory::RegisterVRAMIndexForTile( u32 identifier, u32 VRAMIndex )
	{
		IdentifierToVRAMIndex[identifier] = VRAMIndex;
	}

	//-------------------------------------------------------------------------------------------------
	finline bool TileMemory::TileInVRAM( u32 identifier ) const
	{
		return VRAMIndexForTile(identifier) != -1;
	}

	//-------------------------------------------------------------------------------------------------
	finline int TileMemory::VRAMIndexForTile( u32 identifier ) const
	{
		auto it = IdentifierToVRAMIndex.find(identifier);
		return (it == IdentifierToVRAMIndex.end()) ? -1 : it->second;
	}
}