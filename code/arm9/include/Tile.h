#pragma once

#include "types.h"

namespace Graphics
{
	// 4bpp tile (s-tile)
	struct Tile4bpp
	{
		byte Pixels[32];
	};

	// 8bpp tile (d-tile)
	struct Tile8bpp
	{
		byte Pixels[64];
	};

	/*
	Class that describes an 8x8 pixel tile
	*/
	class Tile
	{
	public:

		///
		Tile(int bpp);

		///
		Tile(const Tile4bpp &tile);

		///
		Tile(const Tile8bpp &tile);

		///
		Ptr< List<byte> > GetPixelData() const;
		
		/// Returns the value of the pixel at the given index. Index is the pixel index [0-63]
		int GetPixel(int index) const;

		/// Sets the value of the pixel. Index is the pixel index [0-63], value is an index in the palette
		void SetPixel(int index, int value);

	public:

		int Bpp;      // Number of bits per pixel of this tile, can be either 4 or 8
		int ByteSize; // Size in bytes of this tile, can be either 32 (for 4bpp tiles) or 64 (for 8bpp tiles)
		u32 Identfier;
		Ptr< List<byte> > Pixels; // Todo: Rename, Pixels[0] for instance does not give you the first pixel in case of 4bpp, but the first and the second
	};

	//-------------------------------------------------------------------------------------------------
	inline Tile::Tile(int bpp) : Bpp(bpp), ByteSize(bpp * 64 / 8)
	{
		Pixels = New< List<byte> >();
		Pixels->resize(ByteSize);
	}

	//-------------------------------------------------------------------------------------------------
	inline Tile::Tile(const Tile4bpp &tile) : Tile(4)
	{
		Pixels->assign(tile.Pixels, tile.Pixels+32);
	}

	//-------------------------------------------------------------------------------------------------
	inline Tile::Tile(const Tile8bpp &tile) : Tile(8)
	{
		Pixels->assign(tile.Pixels, tile.Pixels+64);
	}

	//-------------------------------------------------------------------------------------------------
	inline Ptr< List<byte> > Tile::GetPixelData() const
	{
		return Pixels;
	}
}