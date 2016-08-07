#pragma once

#include "core/types.h"
#include "TileSet.h"

namespace Graphics
{
	class TileSet256 : public TileSet
	{
	private:

		using super = Graphics::TileSet;

	public:

		///
		virtual ~TileSet256() = default;

		///
		void AddTiles(const List<Tile8bpp> &tiles);
	};

	//-------------------------------------------------------------------------------------------------
	inline void TileSet256::AddTiles(const List<Tile8bpp> &tiles)
	{
		for(u32 i = 0; i < tiles.size(); ++i)
			AddTile(tiles[i]);
	}
}