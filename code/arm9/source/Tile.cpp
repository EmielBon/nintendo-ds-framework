#include "Tile.h"

#include "Debug.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	int Tile::GetPixel(int index) const
	{
		sassert(index >= 0 && index < 64, "Pixel index out of range");
		sassert(Pixels, "Pixel data was released, cannot access");
		
		auto &pixels = *Pixels;
		
		if (Bpp == 4)
			return (index % 2 == 0) ? pixels[index/2] >> 4 : pixels[index/2] & 0xF;
		return pixels[index];
	}

	//-------------------------------------------------------------------------------------------------
	void Tile::SetPixel(int index, int value)
	{
		sassert(index >= 0 && index < 64, "Pixel index out of range");
		sassert(Pixels, "Pixel data was released, cannot access");
		
		auto &pixels = *Pixels;

		if (Bpp == 4)
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
}