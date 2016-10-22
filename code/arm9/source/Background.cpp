#include "Background.h"

#include "GraphicsDevice.h"
#include "BackgroundMemory.h"
#include "Debug.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	Background::Background(GraphicsDevice *e, int i) : index(i), graphicsDevice(e), isEnabled(false), type(Tiled32x32), Offset(0, 0), ColorMode(ColorMode16)
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
	void Background::Synchronize()
	{
		ASSERT(graphicsDevice && index != -1, "Background not initialized");
		
		if (!IsEnabled()) 
			return;

		int tileBase = BackgroundMemory().TileBase();

		u16 flags = type | ColorMode | BG_MAP_BASE(0) | BG_TILE_BASE(tileBase) | BG_PRIORITY(layer);

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

	void Background::SetType(BackgroundType newType)
	{
		int mode = graphicsDevice->GetMode();

		bool typeIsTrueColorBitmap = type == TrueColorBitmap128x128 || type == TrueColorBitmap256x256 ||
			                         type == TrueColorBitmap512x256 || type == TrueColorBitmap512x512;

		sassert(IMPLIES(typeIsTrueColorBitmap, mode == 5), "TrueColor bitmaps are not supported in mode %i", mode);

		type = newType;
	}

	void Background::SetBackground2Transformation(const Mat<fx8> &transform) 
	{
		REG_BG2PA = transform[0].number;
		REG_BG2PB = transform[1].number;
		REG_BG2PC = transform[4].number;
		REG_BG2PD = transform[5].number;
	}

	void Background::SetBackground3Transformation(const Mat<fx8> &transform)
	{
		REG_BG3PA = transform[0].number;
		REG_BG3PB = transform[1].number;
		REG_BG3PC = transform[4].number;
		REG_BG3PD = transform[5].number;
	}
}
