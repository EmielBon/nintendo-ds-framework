#include "apps/TimerTest.h"
#include "system/Timer.h"
#include "debug/Logging.h"
#include <nds/timers.h>

namespace Test
{
	using namespace Debug;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	void TimerTest::Initialize()
	{
		secondsTimer = Timer::Start();
	}

	//-------------------------------------------------------------------------------------------------
	void TimerTest::Update(const GameTime &gameTime)
	{
		LOG_CLEAR();

		LOG("Game started " << secondsTimer->GetTimeMilliseconds() / 1000 << " seconds ago");

		if (elapsedMillisecondsTimer)
		{
			LOG("Ms since last update: " << elapsedMillisecondsTimer->GetTimeMilliseconds());
		}

		elapsedMillisecondsTimer = Timer::Start();

		super::Update(gameTime);
	}
}