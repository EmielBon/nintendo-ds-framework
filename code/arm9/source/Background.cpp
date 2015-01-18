#include "Background.h"

#include "GraphicsDevice.h"
#include "BackgroundMemory.h"
#include "Debug.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	Background::Background(GraphicsDevice *e, int i) : index(i), graphicsDevice(e), Offset(0, 0), ColorMode(ColorMode256)
	{
		mapIndex = index;
		layer    = index;
	}

	//-------------------------------------------------------------------------------------------------
	Map* Background::GetMap() const
	{
		return graphicsDevice->BackgroundMemory->Maps[mapIndex].get();
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
		GetMap()->Clear();
	}

	//-------------------------------------------------------------------------------------------------
	void Background::Synchronize() const
	{
		ASSERT(graphicsDevice && index != -1, "Background not initialized");
		
		if (!IsEnabled()) 
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