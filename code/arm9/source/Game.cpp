#include "Game.h"

#include "GraphicsDevice.h"
#include "VideoRam.h"
#include "Logging.h"
#include "Input.h"
#include "DrawableGameComponent.h"
#include "Console.h"
#include "NDSGameHost.h"
#include "Timer.h"

// libnds
#include <filesystem.h>
#include <nds/interrupts.h>
#include <nds/arm9/videoGL.h>

namespace Framework
{
	using namespace std;
	using namespace Debug;
	using namespace Input;
	using namespace System;
	using namespace Graphics;

	Game* Game::instance = NULL;
	GameTime Game::gameTime;

	//-------------------------------------------------------------------------------------------------
	Game::Game() : GraphicsDevice(GraphicsDevice::Main), IsFixedTimeStep(true), inRun(false) 
	{
		// Initialize OpenGL(ish) state machine for 3D functions
		glInit();
		glEnable(GL_TEXTURE_2D);

		gameHost = New<NDSGameHost>(this);
		gameTime = GameTime(0, 0, 0, 0);
		gameTimer = Timer::Start();

		//irqSet(IRQ_VBLANK, VBlankDraw);

		instance = this;
	}

	//-------------------------------------------------------------------------------------------------
	Game& Game::Instance()
	{
		sassert(instance != NULL, "Error: No game instance exists");
		return *instance;
	}

	//-------------------------------------------------------------------------------------------------
	void Game::VBlankDraw()
	{
		Game::Instance().Draw(gameTime);
		GraphicsDevice::Main.Synchronize();
		GraphicsDevice::Sub.Synchronize();
	}

	//-------------------------------------------------------------------------------------------------
	void Game::Run()
	{
		if (inRun)
		{
			LOG_WARNING("Run method called more than once");
			return;
		}
		inRun = true;

		// Initialize file system
		fileSystemSupported = nitroFSInit(NULL);
		// Initialize VRAM
		VideoRam::Initialize();
		// Initialize the engines
		GraphicsDevice::Main.Initialize();
		GraphicsDevice::Sub.Initialize();
		// Enable sprites
		GraphicsDevice::Main.EnableSprites(true);
		GraphicsDevice::Sub.EnableSprites(true);
		// Set the memory addressing mode for sprites
		GraphicsDevice::Main.ObjectAttributeMemory.DisplayMode = SpriteDisplayMode_1D_64;
		GraphicsDevice::Sub.ObjectAttributeMemory.DisplayMode = SpriteDisplayMode_1D_64;
		// Initialize the console
		//InitializeConsole(GraphicsDevice::Sub.Background3);
		LOG("======== Initializing =========");
		LOG("");
		// Calls the pure virtual method Initialize, to let a subclass initialize stuff before loading content
		Initialize();
		// Print some logging layout
		LOG("");
		LOG("======= Loading content =======");
		LOG("");
		// Calls the pure virtual method LoadContent, to let a subclass load content using the initialized hardware
		LoadContent();
		// 'Start' the runtime log
		LOG("");
		LOG("========= Runtime log =========");
		LOG("");
		// Main loop
		gameHost->Run();
	}

	//-------------------------------------------------------------------------------------------------
	void Game::Tick()
	{
		accumulatedElapsedTime = gameTimer->Ticks();
		gameTimer->Stop();
		gameTimer = Timer::Start();
		// Do not allow any update to take longer than our maximum.
		//if (accumulatedElapsedTime > maxElapsedTime)
		//	accumulatedElapsedTime = maxElapsedTime;
		// Perform a single variable length update.
		gameTime.ElapsedGameTime = accumulatedElapsedTime;
		gameTime.TotalGameTime += accumulatedElapsedTime;
		//accumulatedElapsedTime = TimeSpan::Zero;
		// Always set the RunningSlowly flag to false here when we are in fast-as-possible mode.
		gameTime.IsRunningSlowly = false;
		// Read input from the key pad and touch screen
		KeyPad::ReadState();
		TouchScreen::ReadState();
		// Calls the pure virtual method Update, to let a subclass update their data before redrawing
		Update(gameTime);
		// Draw unless the update suppressed it.
		if (suppressDraw)
		{
			suppressDraw = false;
		}
		else
		{
			// Calls the pure virtual method Draw, to let a subclass specify what to draw
			Draw(gameTime);
		}
		// Todo: Check if sprites are enabled
		GraphicsDevice::Main.Synchronize();
		// Todo: Check if sprites are enabled
		GraphicsDevice::Sub.Synchronize();
		// Keep the ARM9 idle until drawing is done
		// Todo: hide
		glFlush(0);
		//swiWaitForVBlank();
	}

	//-------------------------------------------------------------------------------------------------
	void Game::Exit()
	{
		gameHost->Exit();
	}

	//-------------------------------------------------------------------------------------------------
	void Game::Initialize()
	{
		for(auto it = Components.Begin(); it != Components.End(); ++it)
		{
			(*it)->Initialize();
		}
	}

	//-------------------------------------------------------------------------------------------------
	void Game::LoadContent()
	{
		for(auto it = Components.Begin(); it != Components.End(); ++it)
		{
			if (auto drawable = static_cast<DrawableGameComponent*>(*it))
				drawable->LoadContent();
		}
	}

	//-------------------------------------------------------------------------------------------------
	void Game::Update(const GameTime &gameTime)
	{
		for(auto it = Components.Begin(); it != Components.End(); ++it)
		{
			if ((*it)->Enabled)
				(*it)->Update(gameTime);
		}
	}

	//-------------------------------------------------------------------------------------------------
	void Game::Draw(const GameTime &gameTime)
	{
		for(auto it = Components.Begin(); it != Components.End(); ++it)
		{
			if (auto drawable = dynamic_cast<DrawableGameComponent*>(*it))
			{
				if (drawable->Visible)
					drawable->Draw(gameTime);
			}
		}
	}
}