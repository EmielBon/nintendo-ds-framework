#include "TextRenderer.h"
#include "TiledBackground.h"
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
	TextRenderer::TextRenderer(Graphics::Background *background, const String &fontName /* = "font8x8@4" */) 
		: FontName(fontName), dynamicPaletteStartIndex(-1), Background(background)
	{
		
	}

	//-------------------------------------------------------------------------------------------------
	void TextRenderer::LoadContent()
	{
		auto &bgmem = Background->BackgroundMemory();
		Font = ContentManager::Load<Graphics::Font>(FontName);
		// Create and add the font's (dynamic) palette
		AddColor(Color::White, Color::Black); // Standard colors, black bg and white text
		dynamicPaletteStartIndex = bgmem.PaletteMemory->AddDynamicPalette(Palettes);
		// Set the map's clear tile to the font's first glyph. todo: This makes little sense, it takes the first 8x8 tile in the tileset
		auto &blankTile = Font->Tiles[0];
		bgmem.AddTile(blankTile, 0);
		u32 blankTileIndex = bgmem.VRAMIndexForTile(blankTile.Identifier);
		int index = Background->GetMapIndex();
		sassert(index >= 0 && index <= 3, "Map index out of bounds");
		bgmem.Maps[index]->ClearTile = ScreenBlockEntry(blankTileIndex);
	}

	//-------------------------------------------------------------------------------------------------
	void TextRenderer::AddColor(u16 foregroundColor, u16 backgroundColor /* = 0xD59F */)
	{
		sassert(dynamicPaletteStartIndex == -1, "Cannot add colors after copying palettes to palette memory");
		auto pal = New<Palette>();
		pal->AddColor(backgroundColor); // Transparent color
		pal->AddColor(foregroundColor);
		Palettes.push_back(pal);
	}

	//-------------------------------------------------------------------------------------------------
	void TextRenderer::DrawText(const String &str, int x, int y, int paletteIndex)
	{
		sassert(dynamicPaletteStartIndex != -1, "Cannot draw text without a (dynamic) palette");
		
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
		
		int palIndex = dynamicPaletteStartIndex / 16;

		for(u32 i = 0; i < str.length(); ++i)
		{
			for(int j = 0; j < tilesPerChar; ++j)
			{
				int x2 = x + j % charWidth;
				int y2 = y + j / charWidth;
				
				if (x2 < 0 || x2 >= mapWidth8x8 || y2 < 0 || y2 >= mapHeight8x8) 
					continue;

				auto &tile = Font->Tiles[str[i] * tilesPerChar + j];
				//int tileIndex = bgmem.AddTile(tile, dynamicPaletteStartIndex);
				GraphicsDevice::SetBackgroundTile(*Background, i, j, &tile, TileParameters(0, false, false, palIndex));
				//map->SetTile(x2, y2, ScreenBlockEntry(tileIndex, false, false, palIndex));
			}
			x += charWidth;
		}
	}
}