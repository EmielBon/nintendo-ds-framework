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
	uint32_t TileMemory::AddTile(const Tile &tile)
	{
		sassert(PaletteMemory, "Error: Palette memory not initialized");
		// todo: find a way to retrieve dynamicPaletteStartIndex from the tile or its palettes
		
		// Check if tile is already in memory. If so, return the current VRAM index
		int vramIndex = VRAMIndexForTile(tile.Identifier);
		if (vramIndex != -1) {
			return vramIndex;
		}
		
		AddPixelColorsFromTileToPaletteMemory(tile);

		// Map the tile's pixels to colors in palette memory
		Tile palettedTile = PalettedTileFromTile(tile);
		// Generate a new free location for the next addition
		vramIndex = nextAvailableIndex++;
		// Copy the tile to the next available VRAM location
		// todo: wont this overwrite stuff if 4bpp tiles are added second?
		uint16_t* location = TileBaseAddress() + vramIndex * palettedTile.ByteSize() / sizeof(uint16_t);
		bool success = Add(palettedTile.Pixels, location);
		sassert(success, "Failed to copy tiles to VRAM");
		// Register the identifier to the VRAM location
		RegisterVRAMIndexForTile(tile.Identifier, vramIndex);
		sassert(TileInVRAM(tile.Identifier), "Failed to add tile to VRAM");
		return vramIndex;
	}
	
	//-------------------------------------------------------------------------------------------------
	void TileMemory::AddPixelColorsFromTileToPaletteMemory(const Tile &tile)
	{
		Color *pixels = (Color *)tile.Pixels.data();

		for (int i = 0; i < 64; ++i)
		{
			PaletteMemory->AddColor(pixels[i]);
		}
	}

	//-------------------------------------------------------------------------------------------------
	Tile TileMemory::PalettedTileFromTile(const Tile &tile)
	{
		// TODO: Support 4bpp (dynamic palette)
		Tile palettedTile(8);
		
		for (int i = 0; i < 64; ++i)
		{
			Color pixel = tile.GetPixel(i);
			if (pixel == tile.TransparentColor) {
				palettedTile.SetPixel(i, 0);
				continue;
			}
			int colorIndex = PaletteMemory->GetIndexForColor(pixel);
			sassert(colorIndex != -1, "Error: Color %x not present in Palette Memory", (int)pixel);
			palettedTile.SetPixel(i, colorIndex);
		}

		return palettedTile;
	}
}
