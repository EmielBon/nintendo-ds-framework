#include "CollisionMap.h"

namespace Framework2D
{
	//-------------------------------------------------------------------------------------------------
	bool CollisionMap::Collision(int x, int y) const
	{
		int tile = GetTileFor(x, y);
		return ( tile != -1 && Colors[tile] != 0 );
	}

	//-------------------------------------------------------------------------------------------------
	int CollisionMap::GetTileFor(int x, int y) const
	{
		int tile = (x / 8) + (y / 8) * Size.Width;

		if (tile > Size.Width * Size.Height - 1)
			return -1;

		return tile;
	}
}