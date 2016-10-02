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
	Console::Console(Graphics::Background *background) 
		: super(background, "font8x8"), startEntry(-1)
	{
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
		int newStartEntry = Background->Offset.y / 8;

		if (newStartEntry == startEntry)
			return;

		startEntry = newStartEntry;
		// todo: replace this with something
		//Background->Clear();

		// Todo: clean up
		int charWidth = Font->CharSize().Width;
		//int charHeight = Font->CharSize().Height;
		//int charHeight8x8 = charHeight / 8;

		//int startRow   = Background->Offset.y / 8;

		for(int i = 0; i < 26; ++i)
		{
			int entryIndex = startEntry + i;
			//getText(entryIndex);
			if (entryIndex < 0 || entryIndex >= EntryCount())
				break;

			//if (i * charHeight >= Height)
			//	break;

			String text = entries[entryIndex];
			int textWidth = Font->WidthForString(text);
			text = (textWidth < 256) ? text : Font->StringForWidth(text, 256 - 2 * charWidth) + "..";
			//int y = (startRow + entryIndex * charHeight8x8)% 32 ;
			int y = entryIndex % 32;
			DrawText(text, 0, y, 0);
		}

		super::Draw(gameTime);
	}
	
}
