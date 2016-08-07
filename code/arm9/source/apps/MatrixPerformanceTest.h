#pragma once

#include "Game.h"
#include "core/types.h"

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