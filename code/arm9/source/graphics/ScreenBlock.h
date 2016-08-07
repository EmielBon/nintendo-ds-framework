#pragma once

#include "core/types.h"

namespace Graphics
{
	struct ScreenBlock
	{
	public:

		ScreenBlock();

		ScreenBlock(Ptr<Graphics::TileSet> tileSet, Ptr<Graphics::Palette> palette, int tileIndex, bool flipHorizontal, bool flipVertical);

	public:

		Ptr<Graphics::TileSet> TileSet;
		Ptr<Graphics::Palette> Palette;
		int  TileIndex;
		bool FlipHorizontal;
		bool FlipVertical;
	};

	//-------------------------------------------------------------------------------------------------
	inline ScreenBlock::ScreenBlock() 
		: TileIndex(0), FlipHorizontal(false), FlipVertical(false)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline ScreenBlock::ScreenBlock(Ptr<Graphics::TileSet> set, Ptr<Graphics::Palette> pal, int index, bool flipHor, bool flipVer)
		: TileSet(set), Palette(pal), TileIndex(index), FlipHorizontal(flipHor), FlipVertical(flipVer)
	{

	}
}