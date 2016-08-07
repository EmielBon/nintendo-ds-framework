#include "graphics/Tile.h"
#include "graphics/Palette.h"
#include "debug/Debug.h"

namespace Graphics
{
	u32 Tile::nextFreeIdentifier = 1;
	
	//-------------------------------------------------------------------------------------------------
	int Tile::GetPixel(int index) const
	{
		sassert(index >= 0 && index < 64, "Pixel index out of range");
		sassert(Pixels, "Getter : Pixel data was released, cannot access");
		
		auto &pixels = *Pixels;
		
		if (BitsPerPixel() == 4)
			return (index % 2 == 0) ? pixels[index/2] >> 4 : pixels[index/2] & 0xF;
		return pixels[index];
	}

	//-------------------------------------------------------------------------------------------------
	void Tile::SetPixel(int index, int value)
	{
		sassert(index >= 0 && index < 64, "Pixel index out of range");
		sassert(Pixels, "Setter: Pixel data was released, cannot access");
		
		auto &pixels = *Pixels;

		if (BitsPerPixel() == 4)
		{
			byte& pixel  = pixels[index/2];
			int   mask   = (index % 2 == 0) ? 0xF : 0xF0; 
			int   newpix = (index % 2 == 0) ? value << 4 : value;
			pixel = (pixel & mask) | newpix;
		}
		else
		{
			pixels[index] = value;
		}
	}
	
	//-------------------------------------------------------------------------------------------------
	void Tile::AddPalette(Palette *palette)
	{
		sassert(!palette->IsEmpty(), "Cannot add an empty palette to a tile");
		Palettes.push_back(palette);
		// Bpp == 8 implies having 1 palette after adding
		sassert(!(BitsPerPixel() == 8) || Palettes.size() == 1, "Cannot add more than 1 palette to an 8bpp tile");
		sassert(Palettes.size() <= 16, "Cannot add more than 16 palettes to a tile");
	}
}