#include "Background.h"

#include "GraphicsDevice.h"
#include "BackgroundMemory.h"
#include "Debug.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	Background::Background(GraphicsDevice *e, int i) : index(i), layer(3), enabled(false), graphicsDevice(e), mapIndex(-1), Offset(0, 0), ColorMode(ColorMode16)
	{
		
	}

	//-------------------------------------------------------------------------------------------------
	Graphics::BackgroundMemory& Background::BackgroundMemory() const
	{
		return *graphicsDevice->BackgroundMemory;
	}

	//-------------------------------------------------------------------------------------------------
	void Background::Clear()
	{
		ASSERT2(mapIndex >= 0, "No map for Background" << index);
		graphicsDevice->BackgroundMemory->Maps[mapIndex]->Clear();
	}

	//-------------------------------------------------------------------------------------------------
	void Background::Synchronize() const
	{
		ASSERT(graphicsDevice != NULL && index != -1, "Background not initialized");
		
		if (!enabled || mapIndex < 0) 
			return;

		int tileBase = BackgroundMemory().TileBase();

		u16 flags = BG_32x32 | ColorMode | BG_MAP_BASE(mapIndex) | BG_TILE_BASE(tileBase) | BG_PRIORITY(layer);
		bg_scroll scroll = { (u16)Offset.x, (u16)Offset.y };

		if (graphicsDevice->IsMain())
		{
			BACKGROUND.control[index] = flags;
			BACKGROUND.scroll[index] = scroll;
		}
		else
		{
			BACKGROUND_SUB.control[index] = flags;
			BACKGROUND_SUB.scroll[index] = scroll;
		}
	}

}