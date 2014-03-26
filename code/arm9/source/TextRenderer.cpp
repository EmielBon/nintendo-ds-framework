#include "TextRenderer.h"
#include "TiledBackground.h"
#include "Background.h"
#include "ContentManager.h"
#include "GraphicsDevice.h"
#include "BackgroundMemory.h"
#include "Color.h"
#include "Font.h"
#include "Screen.h"
#include "TilesManager.h"

// Debugging
#include "Logging.h"

namespace Graphics
{
	using namespace Graphics;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	TextRenderer::TextRenderer(Graphics::Background &background, const String &fontName /* = "font8x8@4" */) : FontName(fontName), TransparentFont(true), Background(background)
	{
		
	}

	//-------------------------------------------------------------------------------------------------
	void TextRenderer::LoadContent()
	{
		Font = ContentManager::Load<Graphics::Font>(FontName);
		Font->Transparent = TransparentFont;
		AddColor(Color::White, Color::Black); // Standard colors, black bg and white text
		Background.GetMap()->SetClearTile(TilesManager::IdentifierForTile(Font, 0));
	}

	//-------------------------------------------------------------------------------------------------
	void TextRenderer::AddColor(u16 foregroundColor, u16 backgroundColor /* = 0xD59F */)
	{
		Ptr<Palette> pal = New<Palette>();
		pal->AddColor(backgroundColor); // Transparent color
		pal->AddColor(foregroundColor);
		Font->AddPalette(pal);
	}

	//-------------------------------------------------------------------------------------------------
	void TextRenderer::DrawText(const String &str, int x, int y, int palIndex)
	{
		//PROFILE_METHOD(TRDrwT);
		auto &map = *Background.GetMap();
		auto size = map.GetSize();
		
		int charWidth  = Font->CharSize().Width  / 8;
		int charHeight = Font->CharSize().Height / 8;

		int tilesPerChar = charWidth * charHeight;

		int mapWidth8x8  = size.Width;
		int mapHeight8x8 = size.Height;

		MapTile tile;

		for(u32 i = 0; i < str.length(); ++i)
		{
			for(int j = 0; j < tilesPerChar; ++j)
			{
				int x2 = x + j % charWidth;
				int y2 = y + j / charWidth;
				
				if (x2 < 0 || x2 >= mapWidth8x8 || y2 < 0 || y2 >= mapHeight8x8) 
					continue;

				tile.TileIdentifier = TilesManager::IdentifierForTile(Font, str[i] * tilesPerChar + j);
				tile.PaletteIndex = palIndex;
				map.SetTile(x2, y2, tile);
			}
			x += charWidth;
		}
	}
}