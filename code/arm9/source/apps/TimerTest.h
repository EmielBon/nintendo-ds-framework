#pragma once

#include "game/Game.h"
#include "core/types.h"

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