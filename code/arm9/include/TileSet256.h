#pragma once

#include "types.h"
#include "TileSet.h"

namespace Graphics
{
	class TileSet256 : public TileSet
	{
	private:

		using super = Graphics::TileSet;

	public:

		///
		TileSet256() = default;

		///
		virtual ~TileSet256() = default;

		///
		void AddTiles(const List<Tile8bpp> &tiles);

		/// Add a palette to this tile set
		void SetPalette(Ptr<Palette> palette);
	};

	//-------------------------------------------------------------------------------------------------
	inline void TileSet256::AddTiles(const List<Tile8bpp> &tiles)
	{
		for(u32 i = 0; i < tiles.size(); ++i)
		{
			AddTile(tiles[i]);
		}
	}

	//-------------------------------------------------------------------------------------------------
	inline void TileSet256::SetPalette(Ptr<Palette> palette)
	{
		if (Palettes.size() == 0) 
			AddPalette(palette);
		else Palettes[0] = palette;
	}
}