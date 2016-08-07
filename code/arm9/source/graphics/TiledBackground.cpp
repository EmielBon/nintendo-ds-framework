#include "graphics/TiledBackground.h"
#include "graphics/Tile.h"
#include "debug/Debug.h"
#include "graphics/BackgroundMemory.h"
#include "graphics/Background.h"
#include "graphics/GraphicsDevice.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	void TiledBackground::CopyToHardwareBackground(Background &bg) const
	{
		auto map = bg.BackgroundMemory().Maps[bg.GetMapIndex()];

		for (int i = 0; i < Size.Width;  ++i)
		for (int j = 0; j < Size.Height; ++j)
		{
			auto tile   = GetTile(i, j);
			sassert(tile, "Tile (%i,%i) was null", i, j);
			auto params = TileParameters[GetTileIndex(i, j)];
			GraphicsDevice::SetBackgroundTile(bg, i, j, tile, params);
		}
	}
}