#include "TileMemory.h"
#include "PaletteMemory.h"
#include "Tile.h"
#include "Debug.h"

namespace Graphics
{
	using namespace Util;
	using namespace Debug;

	//-------------------------------------------------------------------------------------------------
	TileMemory::TileMemory(bool isMain, u32 type) : super(isMain, type), nextAvailableIndex(0)
	{
		PaletteMemory = New<Graphics::PaletteMemory>(isMain, type | Memory_PAL);
	}

	//-------------------------------------------------------------------------------------------------
	u32 TileMemory::AddTile(const Tile &tile, int dynamicPaletteStartIndex)
	{
		sassert(PaletteMemory, "Error: Palette memory not initialized");
		// todo: find a way to retrieve dynamicPaletteStartIndex from the tile or its palettes
		
		// Check if tile is already in memory. If so, return the current VRAM index
		int vramIndex = VRAMIndexForTile(tile.Identifier);
		if (vramIndex != -1)
			return vramIndex;
		
		// Map the tile's pixels to colors in palette memory
		Ptr<List<byte>> offsetPixels;
		if (tile.BitsPerPixel() == 8)
		{
			offsetPixels = OffsetPixelsForTile(tile);
		}	
		else
		{
			// todo: assumes the dynamic palette is already completely in PaletteMemory
			sassert(dynamicPaletteStartIndex != -1, "Dynamic palette start index not set in call to AddTile");
			offsetPixels = OffsetPixelsForTile(tile, dynamicPaletteStartIndex % 16);
		}
		// Generate a new free location for the next addition
		vramIndex = nextAvailableIndex++;
		// Copy the tile to the next available VRAM location
		// todo: wont this overwrite stuff if 4bpp tiles are added second?
		u16* location = TileBaseAddress() + vramIndex * tile.ByteSize()/sizeof(u16);
		bool success = Add(*offsetPixels, location);
		sassert(success, "Failed to copy tiles to VRAM");
		// Register the identifier to the VRAM location
		RegisterVRAMIndexForTile(tile.Identifier, vramIndex);
		sassert(TileInVRAM(tile.Identifier), "Failed to add tile to VRAM");
		return vramIndex;
	}
	
	//-------------------------------------------------------------------------------------------------
	Ptr< List<byte> > TileMemory::OffsetPixelsForTile(const Tile &tile)
	{
		static int counter = 0;
		
		sassert(tile.Palettes.size() >= 1, "Tile has no referenced Palette");

		// Make empty tile with the same bpp
		Tile offsetTile(tile.BitsPerPixel());
		
		for(int i = 0; i < 64; ++i)
		{
			int pixel = tile.GetPixel(i);
			if (tile.Palettes[0]->Transparent && pixel == 0)
				continue;
			u16 color = tile.Palettes[0]->Colors[pixel];
			int colorIndex = PaletteMemory->AddColor(color);
			offsetTile.SetPixel(i, colorIndex);
		}
		counter++;
		return offsetTile.Pixels;
	}
	
	//-------------------------------------------------------------------------------------------------
	Ptr< List<byte> > TileMemory::OffsetPixelsForTile(const Tile &tile, int offset)
	{
		// Make empty tile with the same bpp
		Tile offsetTile(tile.BitsPerPixel());
		
		for(int i = 0; i < 64; ++i)
		{
			int pixel = tile.GetPixel(i);
			if (tile.Palettes[0]->Transparent && pixel == 0)
				continue;
			offsetTile.SetPixel(i, pixel + offset);
		}
		
		return offsetTile.Pixels;
	}
}