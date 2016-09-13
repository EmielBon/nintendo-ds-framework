#include "PaletteTest.h"
#include "Color.h"
#include "GraphicsDevice.h"
#include "BackgroundMemory.h"
#include "PaletteMemory.h"
#include "X11Palette.h"

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
