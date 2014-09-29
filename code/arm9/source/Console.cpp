#include "Console.h"
#include "TextRenderer.h"
#include "Color.h"
#include "Input.h"
#include "Font.h"
#include "Screen.h"
#include "Background.h"
#include "Assert.h"

namespace System
{
	using namespace Input;
	using namespace Graphics;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	Console::Console(Graphics::Background *background, int x, int y, int width, int height) 
		: super(background, "font8x8@4"), X(x), Y(y), Width(width), Height(height), redraw(true)
	{
		ASSERT(Width % 8 == 0 && Height % 8 == 0, "Invalid Console size");
	}

	//-------------------------------------------------------------------------------------------------
	void Console::Update(const GameTime &gameTime)
	{
		static TouchState oldState;
		
		KeyState   keys  = KeyPad::GetState();
		TouchState touch = TouchScreen::GetState();

		if (keys.IsKeyPressed(Keys::Touch))
		{
			oldState = touch;
		}

		if (keys.IsKeyHeld(Keys::Touch))
		{
			int dy = oldState.Position.py - touch.Position.py;
			Background->Offset.y += dy;
			if (Background->Offset.y < 0)
				Background->Offset.y = 0;
			if (Background->Offset.y > EntryCount() * 8 - Screen::Height)
				Background->Offset.y = EntryCount() * 8 - Screen::Height;
			oldState = touch;
		}
		
		super::Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void Console::Draw(const GameTime &gameTime)
	{
		//if (!redraw)
		//	return;

		// Todo: clean up
		int charWidth     = Font->CharSize().Width;
		int charHeight    = Font->CharSize().Height;
		int charHeight8x8 = charHeight / 8;
		
		int startEntry = Background->Offset.y / 8;
		int startRow   = Background->Offset.y / 8 + 2;

		for(int i = 0; i < 24; ++i)
		{
			int entryIndex = startEntry + i;

			if (entryIndex < 0 || entryIndex >= EntryCount())
				break;

			//if (i * charHeight >= Height)
			//	break;

			String text = entries[entryIndex];
			int textWidth = Font->WidthForString(text);
			text = (textWidth < Width) ? text : Font->StringForWidth(text, Width - 2 * charWidth) + "..";
			DrawText(text, X / 8, (startRow + entryIndex * charHeight8x8) % 32, 0);
		}

		redraw = false;

		super::Draw(gameTime);
	}
	
}