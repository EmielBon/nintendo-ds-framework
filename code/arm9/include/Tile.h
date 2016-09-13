#pragma once

#include "types.h"
#include "Color.h"

namespace Graphics
{
	// 4bpp tile (s-tile)
	struct Tile4bpp
	{
		uint8_t Pixels[32];
	};

	// 8bpp tile (d-tile)
	struct Tile8bpp
	{
		uint8_t Pixels[64];
	};

	// 16bpp tile
	struct Tile16bpp
	{
		uint16_t Pixels[64];
	};

	/*
	Class that describes an 8x8 pixel tile
	*/
	class Tile
	{
	public:

		///
		Tile(int bpp, const void *data = nullptr);

		///
		Tile(const Tile4bpp &tile);

		///
		Tile(const Tile8bpp &tile);

		///
		Tile(const Tile16bpp &tile);

		/// 
		int BitsPerPixel() const;
		
		/// Size in bytes of this tile, can be either 32 (for 4bpp tiles) or 64 (for 8bpp tiles)
		int ByteSize() const;
		
		/// Returns the value of the pixel at the given index. Index is the pixel index [0-63]
		uint16_t GetPixel(int index) const;

		/// Sets the value of the pixel. Index is the pixel index [0-63], value is an index in the palette or a 16 bits color
		void SetPixel(int index, uint16_t value);

	public:

		uint32_t      Identifier;
		List<uint8_t> Pixels; // todo: Rename, Pixels[0] for instance does not give you the first pixel in case of 4bpp, but the first and the second
		Color         TransparentColor;
	};

	//-------------------------------------------------------------------------------------------------
	inline Tile::Tile(int bpp, const void *data /* = nullptr */) : TransparentColor(Color::HotPink)
	{
		static uint32_t nextFreeIdentifier = 0;
		Identifier = nextFreeIdentifier++;
		size_t size = bpp * 64 / 8;
		if (data) {
			Pixels.assign((uint8_t *)data, (uint8_t *)data + size);
		} else {
			Pixels.assign(size, 0);
		}
	}

	//-------------------------------------------------------------------------------------------------
	inline Tile::Tile(const Tile4bpp &tile) : Tile(4, tile.Pixels)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline Tile::Tile(const Tile8bpp &tile) : Tile(8, tile.Pixels)
	{

	}
	
	//-------------------------------------------------------------------------------------------------
	inline Tile::Tile(const Tile16bpp &tile) : Tile(16, tile.Pixels)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline int Tile::BitsPerPixel() const
	{
		return ByteSize() * 8 / 64;
	}
	
	//-------------------------------------------------------------------------------------------------
	inline int Tile::ByteSize() const
	{
		return Pixels.size();
	}
}
