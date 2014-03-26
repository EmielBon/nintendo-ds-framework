#include "Tile.h"

#include "Debug.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	int Tile::GetPixel(int index) const
	{
		ASSERT(index >= 0 && index < 64, "Pixel index out of range");

		if (Bpp == 4)
			return (index % 2 == 0) ? pixels[index/2] >> 4 : pixels[index/2] & 0xF;
		return pixels[index];
	}

	//-------------------------------------------------------------------------------------------------
	int Tile::GetPixel(int x, int y) const
	{
		return GetPixel(x + y * 8);
	}

	//-------------------------------------------------------------------------------------------------
	void Tile::SetPixel(int index, int value)
	{
		ASSERT(index >= 0 && index < 64, "Pixel index out of range");

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

	//-------------------------------------------------------------------------------------------------
	void Tile::SetPixel(int x, int y, int value)
	{
		SetPixel(x + y * 8, value);
	}

	//-------------------------------------------------------------------------------------------------
	void Tile::OffsetPixels(int offset, bool transparent)
	{
		if (offset == 0)
			return;

		for(int i = 0; i < 64; ++i)
		{
			int pixel = GetPixel(i);
			int newPixel = (transparent && pixel == 0) ? 0 : pixel + offset;
			SetPixel(i, newPixel);
		}
	}
}