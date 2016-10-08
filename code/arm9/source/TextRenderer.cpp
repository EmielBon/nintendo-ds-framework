#include "TextRenderer.h"
#include "Background.h"
#include "ContentManager.h"
#include "GraphicsDevice.h"
#include "BackgroundMemory.h"
#include "Color.h"
#include "Font.h"
#include "Screen.h"
#include "ScreenBlockEntry.h"
#include "PaletteMemory.h"

// Debugging
#include "Logging.h"

namespace Graphics
{
	using namespace Graphics;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	TextRenderer::TextRenderer(Graphics::Background *background, const String &fontName /* = "font8x8" */) 
		: FontName(fontName), Background(background)
	{
		
	}

	//-------------------------------------------------------------------------------------------------
	void TextRenderer::LoadContent()
	{
		Font = ContentManager::Load<Graphics::Font>(FontName);
		int index = Background->GetMapIndex();
		sassert(index >= 0 && index <= 3, "Map index out of bounds");
		// Set the map's clear tile to the font's first glyph. todo: This makes little sense, it takes the first 8x8 tile in the tileset
		auto &bgmem = Background->BackgroundMemory();
		auto &blankTile = Font->Tiles[0];
		bgmem.AddTile(blankTile);

		super::LoadContent();
	}

	//-------------------------------------------------------------------------------------------------
	void TextRenderer::DrawText(const String &str, int x, int y, int paletteIndex)
	{
		//PROFILE_METHOD(TRDrwT);
		int index = Background->GetMapIndex();
		sassert(index >= 0 && index <= 3, "Map index out of bounds");
		auto &bgmem = Background->BackgroundMemory();
		auto &map   = bgmem.Maps[index];
		
		// Map size
		auto size = map->GetSize();
		int mapWidth8x8  = size.Width;
		int mapHeight8x8 = size.Height;
		
		// Glyph size and tile count
		int charWidth  = Font->CharSize().Width  / 8;
		int charHeight = Font->CharSize().Height / 8;
		int tilesPerChar = charWidth * charHeight;
		
		int palIndex = 0 / 16;

		for(u32 i = 0; i < str.length(); ++i)
		{
			for(int j = 0; j < tilesPerChar; ++j)
			{
				int x2 = x + j % charWidth;
				int y2 = y + j / charWidth;
				
				if (x2 < 0 || x2 >= mapWidth8x8 || y2 < 0 || y2 >= mapHeight8x8) 
					continue;

				auto &tile = Font->Tiles[str[i] * tilesPerChar + j];
				//GraphicsDevice::SetBackgroundTile(*Background, x2, y2, &tile, TileParameters(0, false, false, palIndex));
				//Background->GetMap()->SetTile(x2, y2, TileParameters(0, false, false, palIndex));
				auto map = Background->GetMap();
				uint32_t tileIndex = GraphicsDevice::Sub.BackgroundMemory->AddTile(tile);
				auto screenBlockEntry = TileParameters(0, false, false, palIndex);
				screenBlockEntry.SetTileIndex(tileIndex);
				map->SetTile(x2, y2, screenBlockEntry);
			}
			x += charWidth;
		}
	}
}
