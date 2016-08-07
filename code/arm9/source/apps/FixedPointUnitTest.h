#pragma once

#include "game/Game.h"

namespace Test
{
	class FixedPointUnitTest : public Framework::Game
	{
	private:

		using super = Framework::Game;

	protected:

		void Initialize();
	};
}