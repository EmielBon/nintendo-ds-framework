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
		TextRenderer(Graphics::Background &background, const String &fontName = "font8x8@4");

		///
		virtual void LoadContent();

		///
		/// Todo: Better solution for palIndex
		void DrawText(const String &str, int x, int y, int palIndex);

		///
		void AddColor(u16 foregroundColor, u16 backgroundColor = 0xD59F/*HotPink*/);

	public:

		String FontName;
		bool TransparentFont;
		Ptr<Graphics::Font> Font;
		Graphics::Background &Background;
		int count;
	};

}