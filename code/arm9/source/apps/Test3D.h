#pragma once

#include "game/Game.h"
#include "core/types.h"
#include "graphics/Color.h"
#include "graphics/BasicEffect.h"
#include "graphics/GraphicsDeviceManager.h"
#include "graphics/Material.h"

namespace Test
{
	class Mario;

	class Test3D : public Framework::Game
	{
	private:

		using super = Framework::Game;

	public:

		Test3D();

		void DrawModel(Model& model);

		void DrawModel(Model& model, Matrix worldMatrix);

		void CheckCollisions();

	protected:

		void Initialize();

		void LoadContent();

		void Update(const GameTime &gameTime);

		void Draw(const GameTime &gameTime);

	public:

		// Often used XNA objects
		GraphicsDeviceManager graphics;
		// Game objects and variables
		Ptr<Mario> mario;
		Ptr<Framework3D::Scene> scene;
	};
}