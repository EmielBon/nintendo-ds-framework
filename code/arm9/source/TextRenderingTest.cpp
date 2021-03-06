#include "TextRenderingTest.h"

// Stable libraries
#include "Input.h"

#include "GraphicsDevice.h"
#include "Background.h"
#include "TextRenderer.h"
#include "PaletteMemory.h"
#include "Color.h"
#include "Logging.h"
#include "TileSet16.h"
#include "Screen.h"

namespace Test
{
	using namespace Input;
	using namespace System;
	using namespace Graphics;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	void TextRenderingTest::Initialize()
	{
		auto bg0 = GraphicsDevice::Main.Backgrounds[0]; // Text layer
		bg0->Enable();
		bg0->SetLayer(0);
		bg0->ShowMapWithIndex(0);

		tr = New<TextRenderer>(bg0);
		Components.Add(tr);

		super::Initialize();
	}

	//-------------------------------------------------------------------------------------------------
	void TextRenderingTest::LoadContent()
	{
		super::LoadContent();
	}

	//-------------------------------------------------------------------------------------------------
	void TextRenderingTest::Update(const GameTime &gameTime)
	{	
		KeyState   keys  = KeyPad::GetState();
		TouchState touch = TouchScreen::GetState();
		
		if (keys.IsKeyHeld(Keys::Touch))
		{
			if (touch.Position.py < 32)
			{
				//Console::SetStartIndex(Console::GetStartIndex() - 1);
			}
			if (touch.Position.py > 192 - 32)
			{
				//Console::SetStartIndex(Console::GetStartIndex() + 1);
			}
		}

		super::Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void TextRenderingTest::Draw(const GameTime &gameTime)
	{
		GraphicsDevice::Main.SetBackgroundColor(Color::CornflowerBlue);

		KeyState   keys   = KeyPad::GetState();
		TouchState touch  = TouchScreen::GetState();

		if (keys.IsKeyHeld(Keys::A))
		{
			tr->DrawText("Test",   20, 4, 0);
			tr->DrawText("Line 2", 20, 6, 0);
		}
		else if (keys.IsKeyHeld(Keys::B))
		{
			tr->DrawText("Nother test", 24, 10, 1);
		}

		if (keys.IsKeyHeld(Keys::Touch))
		{
			Point pos = Screen::Position8x8ForLocation(touch.Position.px, touch.Position.py);
			tr->DrawText("OMG!", pos.x, pos.y, 0);
		}

		super::Draw(gameTime);
	}
}