#pragma once

#include "Game.h"
#include "types.h"

namespace Test
{
	class DebugUITest : public Framework::Game
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