#include "TiledBackground.h"
#include "Tile.h"
#include "Debug.h"
#include "BackgroundMemory.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	void TiledBackground::CheckValid() const
	{
		int width  = Size.Width;
		int height = Size.Height;

		sassert(width  > 0 && width  <= 64 && height > 0 && height <= 64, "Map has invalid dimensions (%ix%i)", width, height);
		sassert((int)TileParameters.size() == width * height, "Map entry count (%i) does not correspond to map size %ix%i = %i", (int)TileParameters.size(), width, height, width * height);
		//ASSERT2(Bpp == 0 || TileByteSize() == Bpp * 64 / 8, "Invalid tile byte size (" << Bpp * 64 / 8 << ")");
	}

	//-------------------------------------------------------------------------------------------------
	void TiledBackground::CopyToHardwareMap(Ptr<Map> map)
	{
		for (int i = 0; i < Size.Width;  ++i)
		for (int j = 0; j < Size.Height; ++j)
		{
			auto tile = GetTile(i, j);
			if (!tile)
			{
				map->SetTile(i, j, map->ClearTile);
				continue;
			}
			sassert(map, "Map not initialized");
			sassert(map->BackgroundMemory, "backgroundmemory not initialized");
			u32 tileIndex = map->BackgroundMemory->AddTile(*tile);
			auto screenBlockEntry = TileParameters[ GetTileIndex(i, j) ];
			screenBlockEntry.SetTileIndex(tileIndex);
			map->SetTile(i, j, screenBlockEntry);
		}
	}
}