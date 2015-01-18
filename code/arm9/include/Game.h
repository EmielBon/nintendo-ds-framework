/**
	@class Framework::Game

	The Game class represents the game flow and is meant to be a superclass.
	The game flow is:
		1. Initialization
		2. Loading Content
		3. 60 times per second Updating / Drawing
	The class is designed to work similar to the Game class in Microsoft's XNA Game Studio

	@author Emiel Bon
 */

#pragma once

#include "types.h"
#include "ContentManager.h"
#include "GraphicsDevice.h"
#include "GameTime.h"

namespace Framework
{
	class IGameComponent;

	class Game
	{
	protected:

		///
		Game();

		/// 
		virtual ~Game() = default;

		///
		static Game& Instance();

	public:

		/// Starts the game. Resets the pre-mapped vram-banks, starts a log and starts the update loop
		void Run();

		/// One processing iteration of the game
		void Tick();

		/// Returns whether the file system was successfully initialized
		bool FileSystemSupported();

		///
		void Exit();

		///
		static void VBlankDraw();

		///
		void AddComponent(GameComponent *component);

		///
		void RemoveComponent(GameComponent *component);

	protected:

		/// This method is called with the subclass' implementation, after initializing the hardware
		virtual void Initialize() { }

		/// This method is called with the subclass' implementation, after Initialize()
		virtual void LoadContent() { }

		/// This method is called with the subclass' implementation, after LoadContent() in an endless loop
		virtual void Update(const GameTime &gameTime);

		/// This method is called with the subclass' implementation, after Update() in an endless loop
		virtual void Draw(const GameTime &gameTime);

	public:

		Framework::ContentManager Content;
		DrawableGameComponent RootComponent;
		// todo: remove, because this is implicitly the main device
		Graphics::GraphicsDevice &GraphicsDevice;
		bool IsFixedTimeStep;

	private:

		bool fileSystemSupported;
		Ptr<IGameHost> gameHost;
		bool inRun;
		bool suppressDraw;

	private:

		System::TimeSpan accumulatedElapsedTime;
		static GameTime gameTime;
		Ptr<Debug::Timer> gameTimer;
		static Game* instance;
	};

	//-------------------------------------------------------------------------------------------------
	inline bool Game::FileSystemSupported()
	{
		return fileSystemSupported;
	}
}