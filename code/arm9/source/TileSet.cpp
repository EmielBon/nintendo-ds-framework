#include "TileSet.h"

namespace Graphics
{
	TiledImage TileSet::GetTiledImageAtIndex(int index) const
	{
		const Tile *startTile = Tiles.data() + index * Get8x8TilesPerTile();
		const Tile *endTile = startTile + Get8x8TilesPerTile();
		List<Tile> tiles(startTile, endTile);
		Size size = GetTileSize();
		return TiledImage(size.Width, size.Height, tiles);
	}
}
