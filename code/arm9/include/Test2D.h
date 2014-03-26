#pragma once

#include "Game2D.h"
#include "types.h"

namespace Test
{
	class Test2D : public Framework2D::Game2D
	{
	private:

		using super = Framework2D::Game2D;

	protected:

		void Initialize();
		void LoadContent();
		void Update(const GameTime &gameTime);
		void Draw(const GameTime &gameTime);

	private:

		Ptr<Debug::DebugUI> debugUI;
		Ptr<Debug::FPSCounter> fpsCounter;
		Ptr<Graphics::SpriteSet> spriteSet;
	};
}