#pragma once

#include "core/types.h"
#include "TileSet.h"

namespace Graphics
{
	class TileSet16 : public TileSet
	{
	private:

		using super = Graphics::TileSet;

	public:

		///
		virtual ~TileSet16() = default;

		///
		void AddTiles(const List<Tile4bpp> &tiles);
	};

	//-------------------------------------------------------------------------------------------------
	inline void TileSet16::AddTiles(const List<Tile4bpp> &tiles)
	{
		for(u32 i = 0; i < tiles.size(); ++i)
			AddTile(tiles[i]);
	}
}