#include "Map.h"
#include "BackgroundMemory.h"
#include "Assert.h"
#include <nds/bios.h>

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	Map::Map(BackgroundMemory* backgroundMemory, int index) : backgroundMemory(backgroundMemory), index(index), size(32, 32)
	{
		location = backgroundMemory->IsMain() ? BG_MAP_RAM(index) : BG_MAP_RAM_SUB(index);
		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	void Map::SetClearTile(const MapTile &tile)
	{
		backgroundMemory->AddTile(tile.TileIdentifier);
		ASSERT(backgroundMemory->TileInVRAM(tile.TileIdentifier), "Failed to add tile to VRAM");
		clearTile = MapTileToScreenBlockEntry(tile);
	}

	//-------------------------------------------------------------------------------------------------
	void Map::Clear()
	{
		u32 tile2 = clearTile | clearTile << 16;
		swiFastCopy(&tile2, location, size.Width * size.Height | COPY_MODE_FILL | COPY_MODE_WORD);
	}

	//-------------------------------------------------------------------------------------------------
	void Map::SetTile(int index, const MapTile &tile)
	{
		// todo: Performance critical method. Find a way to inline this function, without creating a cyclic dependency with BackgroundMemory
		ASSERT(IsInitialized(), "Setting tile in uninitialized map");
		ASSERT(index >= 0 && index < size.Width * size.Height, "Internal map index out of bounds");
		backgroundMemory->AddTile(tile.TileIdentifier);
		ASSERT(backgroundMemory->TileInVRAM(tile.TileIdentifier), "Failed to add tile to VRAM");
		location[index] = MapTileToScreenBlockEntry(tile);
	}

	//-------------------------------------------------------------------------------------------------
	ScreenBlockEntry Map::MapTileToScreenBlockEntry(const MapTile &mapTile) const
	{
		// todo: Performance critical method. Find a way to inline this function, without creating a cyclic dependency with BackgroundMemory
		return ScreenBlockEntry( 
			backgroundMemory->VRAMIndexForIdentifier(mapTile.TileIdentifier), 
			mapTile.FlipHorizontal, 
			mapTile.FlipVertical, 
			mapTile.PaletteIndex );
	}
}