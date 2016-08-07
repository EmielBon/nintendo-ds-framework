#include "TileSet.h"
#include "Palette.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	void TileSet::AddTile(const Tile &tile)
	{
		sassert(TileIsCompatible(tile), "Incompatible tile");
		Tiles.push_back(tile);
	}
}