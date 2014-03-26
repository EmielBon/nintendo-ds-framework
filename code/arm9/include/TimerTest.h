#pragma once

#include "Game.h"
#include "types.h"

namespace Test
{
	class TimerTest : public Framework::Game
	{
	private:

		using super = Framework::Game;

	public:
		
		void Initialize();

		void Update(const Framework::GameTime &gameTime);

	private:

		Ptr<Debug::Timer> secondsTimer;
		Ptr<Debug::Timer> elapsedMillisecondsTimer;
	};
}