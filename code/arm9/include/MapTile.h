#pragma once

#include "types.h"

namespace Graphics
{
	struct MapTile
	{
	public:

		MapTile();

		MapTile(int tileIdentifier);

	public:

		u32  TileIdentifier;
		u32  PaletteIndex;
		bool FlipHorizontal;
		bool FlipVertical;
	};

	//-------------------------------------------------------------------------------------------------
	inline MapTile::MapTile() : TileIdentifier(0), PaletteIndex(0), FlipHorizontal(false), FlipVertical(false)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline MapTile::MapTile(int tileIdentifier) : TileIdentifier(tileIdentifier), PaletteIndex(0), FlipHorizontal(false), FlipVertical(false)
	{

	}
}