#include "Timer.h"
#include <nds/timers.h>
#include <time.h>

namespace Debug
{
	const int Timer::TIMER_SPEED = (BUS_CLOCK/1024);

	//-------------------------------------------------------------------------------------------------
	Ptr<Timer> Timer::Start()
	{
		static bool running = false;

		if (!running)
		{
			timerStart(0, ClockDivider_1024, 0, NULL);
			running = true;
		}

		// Timers should be passed by reference, not by value. Destruction (also implicit) causes the timer to stop
		return New<Timer>();
	}

	//-------------------------------------------------------------------------------------------------
	u64 Timer::GetTotalTicks()
	{
		static bool running = false;
		static u64  totalTicks = 0;

		if (!running)
		{
			timerStart(0, ClockDivider_1024, 0, NULL);
			running = true;
		}

		totalTicks += timerElapsed(0);

		return totalTicks;
	}

}