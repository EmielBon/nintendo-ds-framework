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

		/// 
		TileMemory() = delete;

		virtual ~TileMemory() = default;

		/// Add a single tile to VRAM, returns the VRAM index it was copied to
		uint32_t AddTile(const Tile &tile);

		/// todo: rename
		Tile PalettedTileFromTile(const Tile &tile);

		///
		void RegisterVRAMIndexForTile(uint32_t identifier, u32 VRAMIndex);

		///
		bool TileInVRAM(uint32_t identifier) const;

		///
		int VRAMIndexForTile(uint32_t identifier) const;

	public:

		Ptr<Graphics::PaletteMemory> PaletteMemory;
		int nextAvailableIndex;
		Dictionary<uint32_t, uint32_t> IdentifierToVRAMIndex;
	};

	//-------------------------------------------------------------------------------------------------
	finline void TileMemory::RegisterVRAMIndexForTile( uint32_t identifier, uint32_t VRAMIndex )
	{
		IdentifierToVRAMIndex[identifier] = VRAMIndex;
	}

	//-------------------------------------------------------------------------------------------------
	finline bool TileMemory::TileInVRAM( uint32_t identifier ) const
	{
		return VRAMIndexForTile(identifier) != -1;
	}

	//-------------------------------------------------------------------------------------------------
	finline int TileMemory::VRAMIndexForTile( uint32_t identifier ) const
	{
		auto it = IdentifierToVRAMIndex.find(identifier);
		return (it == IdentifierToVRAMIndex.end()) ? -1 : it->second;
	}
}
