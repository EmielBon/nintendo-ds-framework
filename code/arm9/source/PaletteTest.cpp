#include "PaletteTest.h"
#include "Color.h"
#include "GraphicsDevice.h"
#include "BackgroundMemory.h"
#include "PaletteMemory.h"
#include "Input.h"

namespace Test
{
	using namespace Input;
	using namespace Graphics;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	void PaletteTest::Initialize()
	{
		super::Initialize();
	}

	//-------------------------------------------------------------------------------------------------
	void PaletteTest::LoadContent()
	{
		auto palette = New<X11Palette>();
		
		GraphicsDevice::Main.BackgroundMemory.PaletteMemory.SetTransparentColor(Color::CornflowerBlue);
		GraphicsDevice::Main.BackgroundMemory.PaletteMemory.AddPalette(palette, false);
		
		// Dynamic palette test
		auto pal1 = New<Palette>();
		pal1->AddColor(Color::Gold);
		pal1->AddColor(Color::Red);

		auto pal2 = New<Palette>();
		pal2->AddColor(Color::Blue);
		pal2->AddColor(Color::Green);

		List<Ptr<Palette>> pal2D;
		pal2D.push_back(pal1);
		pal2D.push_back(pal2);
		
		GraphicsDevice::Main.BackgroundMemory.PaletteMemory.AddDynamicPalette(pal2D, false);

		super::LoadContent();
	}

	//-------------------------------------------------------------------------------------------------
	void PaletteTest::Update(const GameTime &gameTime)
	{	
		super::Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void PaletteTest::Draw(const GameTime &gameTime)
	{
		super::Draw(gameTime);
	}
}