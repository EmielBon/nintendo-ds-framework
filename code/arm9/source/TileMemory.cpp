#include "TileMemory.h"

#include "TileSet16.h"
#include "TileSet256.h"
#include "Logging.h"
#include "SetHelper.h"
#include "TilesManager.h"

namespace Graphics
{
	using namespace Util;
	using namespace Debug;

	//-------------------------------------------------------------------------------------------------
	void TileMemory::AddTileUnsafe(u32 identifier)
	{
		// Copy tile
		Tile tile( TilesManager::TileForIdentifier(identifier) ); 
		// Retrieve TileSet
		Ptr<TileSet> tileSet = TilesManager::TileSetForIdentifier(identifier);
		// Add the palette(s) and get offset
		int paletteOffset = -1;
		
		if (tileSet->HasDynamicPalette())
		{
			PaletteMemory.AddDynamicPalette(tileSet->Palettes, tileSet->Transparent);
			paletteOffset = PaletteMemory.GetPosition(tileSet->Palettes[0]).x;
		}
		else
		{
			PaletteMemory.AddPalette(tileSet->Palettes[0], tileSet->Transparent);
			paletteOffset = PaletteMemory.GetIndex(tileSet->Palettes[0]);
		}
		
		ASSERT(PaletteMemory.HasPalette(tileSet->Palettes[0]), "Palette not in memory");

		// Offset the tile's pixels
		tile.OffsetPixels(paletteOffset, tileSet->Transparent);
		// Copy the tile to the next available VRAM location
		// todo: wont this overwrite stuff if 4bpp tiles are added second?
		u16* location = TileBaseAddress() + nextAvailableIndex * tile.ByteSize/sizeof(u16);
		bool success = Add(tile.GetPixelDataRef(), location);
		ASSERT(success, "Failed to copy tiles to VRAM");
		// Register the identifier to the VRAM location
		RegisterVRAMIndexForTile(identifier, nextAvailableIndex);
		// Generate a new free location for the next addition
		nextAvailableIndex++;
	}

	//-------------------------------------------------------------------------------------------------
	void TileMemory::AddTiles(const Set<u32> &identifiers)
	{
		for (auto identifier : identifiers)
			AddTile(identifier);
	}
}