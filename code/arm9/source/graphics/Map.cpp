#include "graphics/Map.h"
#include "graphics/BackgroundMemory.h"
#include "debug/Assert.h"
#include "graphics/Tile.h"
#include <nds/bios.h>

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	Map::Map(Graphics::BackgroundMemory* backgroundMemory, int index) : index(index), size(32, 32), BackgroundMemory(backgroundMemory) 
	{
		sassert(backgroundMemory, "Error: Background memory cannot be null");
		location = BackgroundMemory->IsMain() ? BG_MAP_RAM(index) : BG_MAP_RAM_SUB(index);
		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	void Map::Clear()
	{
		u32 tile2 = ClearTile | ClearTile << 16;
		swiFastCopy(&tile2, location, size.Width * size.Height | COPY_MODE_FILL | COPY_MODE_WORD);
	}
}