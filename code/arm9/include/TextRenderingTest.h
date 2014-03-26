#pragma once

#include "Game.h"
#include "types.h"

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

		Ptr<Graphics::TextRenderer> tr;
	};
}