#pragma once

#include "Game.h"
#include "core/types.h"

namespace Test
{
	class PaletteTest : public Framework::Game
	{
	private:

		using super = Framework::Game;

	protected:

		void Initialize();
		void LoadContent();
		void Update(const GameTime &gameTime);
		void Draw(const GameTime &gameTime);
	};
}