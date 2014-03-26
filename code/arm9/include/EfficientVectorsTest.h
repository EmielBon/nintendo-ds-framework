#pragma once

#include "Game.h"
#include "types.h"
#include "GraphicsDeviceManager.h"

namespace Test
{
	class EVTest : public Framework::Game
	{
	private:

		using super = Framework::Game;

	public:

		EVTest();

	protected:

		void Initialize();

		void LoadContent();

		void Update(const GameTime &gameTime);

		void Draw(const GameTime &gameTime);

	protected:

		// Often used XNA objects
		GraphicsDeviceManager graphics;
		Ptr<VertexBuffer> quadVertices;
		Ptr<IndexBuffer> quadIndices;
		Ptr<BasicEffect> effect;
		Ptr<Camera> camera;
		Ptr<Model> model;
	};
}