#include "apps/PaletteTest.h"
#include "graphics/Color.h"
#include "graphics/GraphicsDevice.h"
#include "graphics/BackgroundMemory.h"
#include "graphics/PaletteMemory.h"
#include "graphics/X11Palette.h"

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
		X11Palette palette;
		
		GraphicsDevice::Main.BackgroundMemory->PaletteMemory->SetTransparentColor(Color::CornflowerBlue);
		for (auto color : palette.Colors)
			GraphicsDevice::Main.BackgroundMemory->PaletteMemory->AddColor(color);
		GraphicsDevice::Main.BackgroundMemory->PaletteMemory->AddColor(Color::Red);
		sassert(false, "%i", GraphicsDevice::Main.BackgroundMemory->PaletteMemory->GetIndexForColor(0xD59F));
		//sassert(false, "%i",GraphicsDevice::Main.BackgroundMemory->PaletteMemory->ColorToPaletteIndex.size());
		// Dynamic palette test
		auto pal1 = New<Palette>();
		pal1->AddColor(Color::Gold);
		pal1->AddColor(Color::Red);
		pal1->Transparent = false;

		auto pal2 = New<Palette>();
		pal2->AddColor(Color::Blue);
		pal2->AddColor(Color::Green);
		pal2->Transparent = false;

		List<Ptr<Palette>> pal2D;
		pal2D.push_back(pal1);
		pal2D.push_back(pal2);
		
		GraphicsDevice::Main.BackgroundMemory->PaletteMemory->AddDynamicPalette(pal2D);

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