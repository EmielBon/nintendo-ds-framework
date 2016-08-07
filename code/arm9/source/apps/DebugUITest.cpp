/*#include "DebugUITest.h"

// Stable packages
#include "game/Framework.h"
#include "input/Input.h"

// Specific classes
#include "graphics/GraphicsDevice.h"
#include "debug/DebugUI.h"
#include "graphics/TileSet256.h"

namespace Test
{
	using namespace Debug;
	using namespace Graphics;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	void DebugUITest::Initialize()
	{
		GraphicsDevice::Main.SetBackgroundColor(Color::CornflowerBlue);
		GraphicsDevice::Sub.SetBackgroundColor(Color::BlueViolet);

		HideConsole();

		Background& bg2 = GraphicsDevice::Sub.Background2;
		bg2.Enable();
		bg2.SetLayer(0);

		auto debugUI = New<DebugUI>(bg2);
		Components.Add(debugUI);

		super::Initialize();
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUITest::LoadContent()
	{
		Ptr<TileSet256> tileSet = Content.Load<TileSet256>("zeldaset");
		tileSet->SetPalette(Content.Load<Palette>("zeldaset_pal"));

		GraphicsDevice::Main.BackgroundMemory.AddTiles(tileSet);

		super::LoadContent();
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUITest::Update(const GameTime &gameTime)
	{	
		super::Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUITest::Draw(const GameTime &gameTime)
	{
		super::Draw(gameTime);
	}
}*/