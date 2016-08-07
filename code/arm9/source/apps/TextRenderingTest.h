#pragma once

#include "game/Game.h"
#include "core/types.h"

namespace Test
{
	class TextRenderingTest : public Framework::Game
	{
	private:

		using super = Framework::Game;

	protected:

		void Initialize();
		void LoadContent();
		void Update(const GameTime &gameTime);
		void Draw(const GameTime &gameTime);

	protected:

		Graphics::TextRenderer *tr;
	};
}