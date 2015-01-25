#include "TiledBackground.h"
#include "Tile.h"
#include "Debug.h"
#include "BackgroundMemory.h"
#include "Background.h"
#include "GraphicsDevice.h"

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
			auto params = TileParameters[GetTileIndex(i, j)];
			GraphicsDevice::SetBackgroundTile(bg, i, j, tile, params);
		}
	}
}