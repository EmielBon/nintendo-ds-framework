#pragma once

#include "Game.h"
#include "types.h"

namespace Test
{
	class MatrixPerformanceTest : public Framework::Game
	{
	private:

		using super = Framework::Game;

	protected:

		void Initialize();
	};
}