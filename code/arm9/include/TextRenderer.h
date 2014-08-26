#pragma once

#include "DrawableGameComponent.h"
#include "Color.h"
#include "types.h"

namespace Graphics
{
	class TextRenderer : public Framework::DrawableGameComponent
	{
	public:

		///
		TextRenderer(Ptr<Graphics::Background> background, const String &fontName = "font8x8@4");

		///
		virtual void LoadContent();

		///
		/// Todo: Better solution for palIndex
		void DrawText(const String &str, int x, int y, int paletteIndex);

		///
		void AddColor(u16 foregroundColor, u16 backgroundColor = 0xD59F/*HotPink*/);

	public:

		String FontName;
		Ptr<Graphics::Font> Font;
		List< Ptr<Palette> > Palettes;
		int dynamicPaletteStartIndex;
		Ptr<Graphics::Background> Background;
		int count;
	};
}