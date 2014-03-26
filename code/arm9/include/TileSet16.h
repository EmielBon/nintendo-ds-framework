#pragma once

#include "types.h"
#include "TileSet.h"

namespace Graphics
{
	class TileSet16 : public TileSet
	{
	private:

		using super = Graphics::TileSet;

	public:

		///
		TileSet16() = default;

		///
		virtual ~TileSet16() = default;

		///
		void AddTiles(const List<Tile4bpp> &tiles);

		/// Add a palette to this tile set
		bool AddPalette(Ptr<Palette> palette);
	};

	//-------------------------------------------------------------------------------------------------
	inline bool TileSet16::AddPalette(Ptr<Palette> palette)
	{
		return super::AddPalette(palette);
	}

	//-------------------------------------------------------------------------------------------------
	inline void TileSet16::AddTiles(const List<Tile4bpp> &tiles)
	{
		for(u32 i = 0; i < tiles.size(); ++i)
		{
			AddTile(tiles[i]);
		}
	}
}