#pragma once

#include "types.h"

namespace Graphics
{
	class TilesManager
	{
	public:

		static void AddTileSet(Ptr<TileSet> tileSet);

		static u32 IdentifierForTileSet(Ptr<TileSet> tileSet);

		static u32 IdentifierForTile(Ptr<TileSet> tileSet, u32 tileIndex);

		static Ptr<TileSet> TileSetForIdentifier(u32 identifier);

		static Tile& TileForIdentifier(u32 identifier);

	private:

		static TreeMap< Ptr<TileSet>, u32 > TileSetToIdentifier;
		static u32 nextFreeIdentifier;

	public:

		static const u32 TILE_NOT_FOUND = -1;
	};
}