#include "Button.h"
#include "Input.h"
#include "TileSet256.h"
#include "Color.h"
#include "TiledBackground.h"
#include "GraphicsDevice.h"
#include "TextRenderer.h"
#include "Background.h"
#include "Font.h"
#include "Vec2.h"

namespace GUI
{
	using namespace Input;
	using namespace Graphics;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	Button::Button(const String &text, int x, int y, Graphics::Background *background)
	{
		Text = text;
		tr = New<TextRenderer>(background, "font8x16@4");
		tr->LoadContent();

		Bounds.Position = Point(x, y);
		Bounds.Size.Width  = tr->Font->WidthForString(text);
		Bounds.Size.Height = tr->Font->CharSize().Height;
	}

	//-------------------------------------------------------------------------------------------------
	void Button::Tap()
	{
		FireActionPerformed(this);
	}

	//-------------------------------------------------------------------------------------------------
	void Button::Update(const GameTime &gameTime)
	{
		auto touch = TouchScreen::GetState();

		if (!touch.IsPressed())
			return;

		int x = touch.Position.px;
		int y = touch.Position.py;
		
		if ( Contains(x, y) )
		{
			Tap();
		}

		super::Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void Button::Draw(const GameTime &gameTime)
	{
		tr->DrawText(Text, Bounds.Position.x / 8, Bounds.Position.y / 8, 0);
		tr->Draw(gameTime);

		super::Draw(gameTime);
	}
}