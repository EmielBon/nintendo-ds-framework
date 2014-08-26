#include "TileSet.h"
#include "Palette.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	bool TileSet::AddTile(const Tile &tile)
	{
		if (!TileIsCompatible(tile))
			return false;

		Tiles.push_back(tile);
		return true;
	}
}