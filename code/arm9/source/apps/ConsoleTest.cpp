#include "ConsoleTest.h"

// Stable packages
#include "game/Framework.h"
#include "input/Input.h"

// Specific classes
#include "graphics/GraphicsDevice.h"
#include "debug/Logging.h"

namespace Test
{
	using namespace Graphics;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	void ConsoleTest::Initialize()
	{
		GraphicsDevice::Main.SetBackgroundColor(Color::CornflowerBlue);
		GraphicsDevice::Sub.SetBackgroundColor(Color::BlueViolet);

		LOG("Initialized stuff");
		super::Initialize();
	}

	//-------------------------------------------------------------------------------------------------
	void ConsoleTest::LoadContent()
	{
		LOG("Loaded stuff");
		LOG("Very long entry that doesn't fit on the screen");
		super::LoadContent();
	}

	//-------------------------------------------------------------------------------------------------
	void ConsoleTest::Update(const GameTime &gameTime)
	{	
		super::Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void ConsoleTest::Draw(const GameTime &gameTime)
	{
		super::Draw(gameTime);
	}
}
