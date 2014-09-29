/**
	@class Graphics::TileSet

	The TileSet class represents a set of 8x8 tiles

	@author Emiel Bon
 */

#pragma once

#include "types.h"
#include "Tile.h"
#include "Size.h"

namespace Graphics
{
	class TileSet
	{
	protected:

		/// Empty Constructor
		TileSet() = default;

	public:

		///
		virtual ~TileSet() = default;

		/// Add a tile to this tile set
		bool AddTile(const Tile &tile);

		/// Get the size of the tiles in this tile set
		Framework::Size GetTileSize() const;

		/// Returns whether this tile set contains any tiles
		bool IsEmpty() const;

		/// Get the number of 8x8 tiles in a tile, depending on the tile size
		int Get8x8TilesPerTile() const;

		/// Get the number of tiles in this tile set, depending by the tile size
		int GetTileCount() const;

		/// Get the number of 8x8 tiles in this tile set
		int GetTileCount8x8() const;
	
		/// Returns the byte size of the tiles in this tile set. Can be 0 (if the set is empty), 4 if it contains 4bpp tiles, or 8 if it contains 8bpp tiles
		int TileByteSize() const;

		/// Returns whether this tile can be added to this tile set
		bool TileIsCompatible(const Tile &tile) const;

		//////////////////////////////////////////////
		// Todo: Overlap with other data containers //
		//////////////////////////////////////////////
		///
		int GetByteSize() const;

	public:

		Framework::Size tileSize;
		// todo: use a list of TiledImages instead of Tiles
		List<Tile> Tiles;
	};

	//-------------------------------------------------------------------------------------------------
	inline Framework::Size TileSet::GetTileSize() const
	{
		return tileSize;
	}

	//-------------------------------------------------------------------------------------------------
	inline int TileSet::GetTileCount() const
	{
		return GetTileCount8x8() / Get8x8TilesPerTile();
	}

	//-------------------------------------------------------------------------------------------------
	inline int TileSet::GetTileCount8x8() const
	{
		return Tiles.size();
	}

	//-------------------------------------------------------------------------------------------------
	inline int TileSet::Get8x8TilesPerTile() const
	{
		return (tileSize.Width / 8) * (tileSize.Height / 8);
	}

	//-------------------------------------------------------------------------------------------------
	inline int TileSet::GetByteSize() const
	{
		return (IsEmpty()) ? 0 : GetTileCount8x8() * TileByteSize();
	}
	
	//-------------------------------------------------------------------------------------------------
	inline int TileSet::TileByteSize() const
	{
		return (IsEmpty()) ? 0 : Tiles[0].ByteSize();
	}

	//-------------------------------------------------------------------------------------------------
	inline bool TileSet::TileIsCompatible(const Tile &tile) const
	{
		return (IsEmpty() || tile.BitsPerPixel() == Tiles[0].BitsPerPixel());
	}

	//-------------------------------------------------------------------------------------------------
	inline bool TileSet::IsEmpty() const
	{
		return (GetTileCount8x8() == 0);
	}
}