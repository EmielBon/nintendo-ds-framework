#pragma once

#include "Size.h"
#include "types.h"
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
		Tile* GetTile(int x, int y) const;

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
	inline Tile* TiledImage::GetTile( int x, int y ) const
	{
		return Tiles[ GetTileIndex(x, y) ];
	}

	//-------------------------------------------------------------------------------------------------
	inline void TiledImage::SetTile( int x, int y, Tile *tile )
	{
		// Assert there are no tiles of different bpp in this map
		sassert(Bpp == tile->BitsPerPixel(), "Cannot add tiles of different bit-depth");
		Tiles[ GetTileIndex(x, y) ] = tile;
	}
}