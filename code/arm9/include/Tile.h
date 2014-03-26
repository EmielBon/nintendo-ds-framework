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
		Tile(const Tile4bpp &tile);

		///
		Tile(const Tile8bpp &tile);

		///
		Tile(const Tile &other);

		///
		Tile(int bpp);

		/// Returns the value of the pixel at the given index. Index is the pixel index [0-63]
		int GetPixel(int index) const;

		///
		int GetPixel(int x, int y) const;

		/// Sets the value of the pixel. Index is the pixel index [0-63], value is an index in the palette
		void SetPixel(int index, int value);

		///
		void SetPixel(int x, int y, int value);

		/// Offset the pixels in this tile. If transparent is true, pixels with value 0 will not be offset
		void OffsetPixels(int offset, bool transparent = false);

		///
		List<byte>& GetPixelDataRef();

		///
		const List<byte>& GetPixelDataRef() const;

	private:

		// Todo: Rename, Pixels[0] for instance does not give you the first pixel in case of 4bpp, but the first and the second
		List<byte> pixels;

	public:

		const int Bpp;      // Number of bits per pixel of this tile, can be either 4 or 8
		const int ByteSize; // Size in bytes of this tile, can be either 32 (for 4bpp tiles) or 64 (for 8bpp tiles)
	};

	//-------------------------------------------------------------------------------------------------
	inline Tile::Tile(const Tile4bpp &tile) : Bpp(4), ByteSize(32)
	{
		pixels.assign(tile.Pixels, tile.Pixels+32);
	}

	//-------------------------------------------------------------------------------------------------
	inline Tile::Tile(const Tile8bpp &tile) : Bpp(8), ByteSize(64)
	{
		pixels.assign(tile.Pixels, tile.Pixels+64);
	}

	//-------------------------------------------------------------------------------------------------
	inline Tile::Tile(const Tile &other) : Bpp(other.Bpp), ByteSize(other.ByteSize)
	{
		pixels = other.pixels;
	}

	//-------------------------------------------------------------------------------------------------
	inline Tile::Tile(int bpp) : Bpp(bpp), ByteSize(bpp * 64 / 8)
	{
		pixels.resize(ByteSize);
	}

	//-------------------------------------------------------------------------------------------------
	inline List<byte>& Tile::GetPixelDataRef()
	{
		return pixels;
	}

	//-------------------------------------------------------------------------------------------------
	inline const List<byte>& Tile::GetPixelDataRef() const
	{
		return pixels;
	}
}

