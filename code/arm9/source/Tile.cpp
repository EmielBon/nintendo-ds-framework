#include "Tile.h"
#include "Palette.h"
#include "Debug.h"

namespace Graphics
{
	uint32_t Tile::nextFreeIdentifier = 0;

	//-------------------------------------------------------------------------------------------------
	uint16_t Tile::GetPixel(int index) const
	{
		sassert(index >= 0 && index < 64, "Pixel index out of range");
		
		int bpp = BitsPerPixel();

		if (bpp == 4) {
			return (index % 2 == 0) ? Pixels[index/2] >> 4 : Pixels[index/2] & 0xF;
		} else if (bpp == 8) {
			return Pixels[index];
		} else if (bpp == 16) {
			auto colors = (uint16_t *)Pixels.data();
			return colors[index];
		}

		sassert(false, "Error: Unsupported number of bits per pixel: %i, size: %i", bpp, ByteSize());
		return 0;
	}

	//-------------------------------------------------------------------------------------------------
	void Tile::SetPixel(int index, uint16_t value)
	{
		sassert(index >= 0 && index < 64, "Pixel index out of range");
		
		int bpp = BitsPerPixel();

		if (bpp == 4) {
			uint16_t rawColor = (uint16_t) value;
			uint8_t& pixel  = Pixels[index/2];
			int   mask   = (index % 2 == 0) ? 0xF : 0xF0; 
			int   newpix = (index % 2 == 0) ? rawColor << 4 : rawColor;
			pixel = (pixel & mask) | newpix;
		} else if (bpp == 8) {
			Pixels[index] = value;
		} else if (bpp == 16) {
			auto pixels = (uint16_t *)Pixels.data();
			pixels[index] = value;
		}
	}
}
