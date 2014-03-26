#pragma once

#include "Game.h"
#include "types.h"

namespace Test
{
	class ProfilingTest : public Framework::Game
	{
	private:

		using super = Framework::Game;

	public:

		void Initialize();

		void DoSomeWork(int i);

	public:

		vs32 counter;
	};
}