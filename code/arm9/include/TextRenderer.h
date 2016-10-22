#pragma once

#include "DrawableGameComponent.h"
#include "Color.h"
#include "types.h"
#include "Palette.h"

namespace Graphics
{
	class TextRenderer : public Framework::DrawableGameComponent
	{
	private:

		using super = Framework::DrawableGameComponent;

	public:

		///
		TextRenderer(Graphics::Background *background, const String &fontName = "font8x8");

		///
		virtual void LoadContent();

		///
		/// Todo: Better solution for palIndex
		void DrawText(const String &str, int x, int y, int paletteIndex);

	public:

		String FontName;
		Ptr<Graphics::TileSet> Font;
		Ptr<Graphics::Palette> Palette;
		Graphics::Background *Background;
	};
}