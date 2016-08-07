#include "graphics/TileSet.h"
#include "graphics/Palette.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	void TileSet::AddTile(const Tile &tile)
	{
		sassert(TileIsCompatible(tile), "Incompatible tile");
		Tiles.push_back(tile);
	}
}