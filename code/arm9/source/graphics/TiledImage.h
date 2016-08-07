#pragma once

#include "Size.h"
#include "core/types.h"
// todo: only here for the bpp assertion in SetTile 
#include "Tile.h"

namespace Graphics
{
	class TiledImage
	{
	public:
	
		/// Empty constructor
		TiledImage();
		
		///
		TiledImage(int width, int height, int bpp);
		
		///
		int GetTileIndex(int x, int y) const;
	
		///
		Tile* GetTile(int i) const;

		///
		Tile* GetTile(int x, int y) const;

		///
		void SetTile(int i, Tile *tile);

		///
		void SetTile(int x, int y, Tile *tile);
		
	public:
		
		List<Tile*> Tiles;
		Framework::Size Size;
		int Bpp;
	};
	
	//-------------------------------------------------------------------------------------------------
	inline TiledImage::TiledImage() : Bpp(0)
	{
		
	}
	
	//-------------------------------------------------------------------------------------------------
	inline TiledImage::TiledImage(int width, int height, int bpp) : Size(width, height), Bpp(bpp)
	{
		Tiles.assign(width * height, nullptr);
	}
	
	//-------------------------------------------------------------------------------------------------
	inline int TiledImage::GetTileIndex(int x, int y) const
	{
		return x + y * Size.Width;
	}

	//-------------------------------------------------------------------------------------------------
	inline Tile* TiledImage::GetTile(int i) const
	{
		return Tiles[i];
	}

	//-------------------------------------------------------------------------------------------------
	inline Tile* TiledImage::GetTile( int x, int y ) const
	{
		return GetTile( GetTileIndex(x, y) );
	}

	//-------------------------------------------------------------------------------------------------
	inline void TiledImage::SetTile(int i, Tile *tile)
	{
		// Assert there are no tiles of different bpp in this map
		sassert(tile, "Cannot set tile to null");
		sassert(Bpp == tile->BitsPerPixel(), "Cannot add tiles of different bit-depth");
		Tiles[i] = tile;
	}

	//-------------------------------------------------------------------------------------------------
	inline void TiledImage::SetTile( int x, int y, Tile *tile )
	{
		Tiles[ GetTileIndex(x, y) ] = tile;
	}
}