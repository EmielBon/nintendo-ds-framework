#pragma once

#include "Size.h"
#include "types.h"
#include "Tile.h"

namespace Graphics
{
	class TiledImage
	{
	public:
		
		///
		TiledImage(int width, int height, const List<Tile> &tiles);
		
		///
		int GetTileIndex(int x, int y) const;

		///
		const Tile& GetTile(int x, int y) const;

		///
		void SetTile(int x, int y, const Tile &tile);

		///
		Tile& operator [](int index);
		
		///
		const Tile& operator [](int index) const;

	public:
		
		List<Tile> Tiles;
		::Size Size;
	};
	
	//-------------------------------------------------------------------------------------------------
	inline TiledImage::TiledImage(int width, int height, const List<Tile> &tiles) : Tiles(tiles), Size(width, height)
	{
		
	}
	
	//-------------------------------------------------------------------------------------------------
	inline int TiledImage::GetTileIndex(int x, int y) const
	{
		return x + y * Size.Width;
	}

	//-------------------------------------------------------------------------------------------------
	inline const Tile& TiledImage::GetTile( int x, int y ) const
	{
		int index = GetTileIndex(x, y);
		return Tiles[index];
	}

	//-------------------------------------------------------------------------------------------------
	inline void TiledImage::SetTile( int x, int y, const Tile &tile )
	{
		int index = GetTileIndex(x, y);
		Tiles[index] = tile;
	}

	//-------------------------------------------------------------------------------------------------
	inline Tile& TiledImage::operator[](int index) 
	{
		return Tiles[index];
	}

	//-------------------------------------------------------------------------------------------------
	inline const Tile& TiledImage::operator[](int index) const
	{
		return Tiles[index];
	}
}
