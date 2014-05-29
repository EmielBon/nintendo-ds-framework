#pragma once

#include "types.h"
#include "MapTile.h"
#include "Size.h"

namespace Graphics
{
	class TiledBackground
	{
	public:
		
		/// Empty constructor
		TiledBackground();
		
		///
		TiledBackground(int width, int height);
		
		///
		static Ptr<TiledBackground> FromTileSet(Ptr<TileSet> tileSet, int width, int height);

		/// Returns the size of this map
		Framework::Size GetSize() const;
		
		/// Returns whether the map is in a valid format to be displayed
		void CheckValid() const;
		
		///
		Set<u32> UniqueIndices() const;

		///
		void Clear();

		///
		int GetTileIndex(int x, int y) const;
	
		///
		int TileByteSize() const;

		///
		const MapTile& GetTile(int index) const;

		///
		const MapTile& GetTile(int x, int y) const;

		///
		void SetTile(int index, const MapTile& mapTile);

		///
		void SetTile(int x, int y, const MapTile& mapTile);

		///
		void CopyToHardwareMap(int mapIndex);

	public:

		List<MapTile> MapTiles;
		Ptr<Framework2D::CollisionMap> CollisionMap;

		// todo: remove const
		const Framework::Size Size;
		TreeMap<u32, int> IdentifierReferenceCount;
		int Bpp;
		//Set<u32> UniqueIndices;
	};

	//-------------------------------------------------------------------------------------------------
	inline TiledBackground::TiledBackground() : Bpp(0)
	{
		
	}

	//-------------------------------------------------------------------------------------------------
	inline TiledBackground::TiledBackground(int w, int h) : Size(w, h), Bpp(0)
	{
		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	inline Framework::Size TiledBackground::GetSize() const
	{
		return Size;
	}

	//-------------------------------------------------------------------------------------------------
	inline int TiledBackground::GetTileIndex(int x, int y) const
	{
		return x + y * Size.Width;
	}

	//-------------------------------------------------------------------------------------------------
	inline const MapTile& TiledBackground::GetTile( int index ) const
	{
		return MapTiles[index];
	}

	//-------------------------------------------------------------------------------------------------
	inline const MapTile& TiledBackground::GetTile( int x, int y ) const
	{
		return GetTile( GetTileIndex(x, y) );
	}

	//-------------------------------------------------------------------------------------------------
	inline void TiledBackground::SetTile( int x, int y, const MapTile& mapTile )
	{
		SetTile(GetTileIndex(x, y), mapTile);
	}

	//-------------------------------------------------------------------------------------------------
	inline int TiledBackground::TileByteSize() const
	{
		return Bpp * 64 / 8;
	}
}