#include "Map.h"
#include "BackgroundMemory.h"
#include "Assert.h"
#include "Tile.h"
#include <nds/bios.h>

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	Map::Map(Graphics::BackgroundMemory* backgroundMemory, int index) : index(index), size(32, 32), BackgroundMemory(backgroundMemory) 
	{
		sassert(backgroundMemory, "Error: Background memory cannot be null");
		location = BackgroundMemory->IsMain() ? BG_MAP_RAM(index) : BG_MAP_RAM_SUB(index);
	}

	//-------------------------------------------------------------------------------------------------
	void Map::Clear(ScreenBlockEntry screenBlockEntry)
	{
		u32 tile2 = screenBlockEntry | screenBlockEntry << 16;
		swiFastCopy(&tile2, location, size.Width * size.Height | COPY_MODE_FILL | COPY_MODE_WORD);
	}
}
