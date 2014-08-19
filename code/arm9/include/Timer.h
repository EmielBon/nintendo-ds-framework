#pragma once

#include "types.h"

// todo: should be in System namespace
namespace Debug
{	
	struct Timer
	{
	public:

		Timer();

		virtual ~Timer();

		static Ptr<Timer> Start();

		void Stop();

		u64 GetTimeMilliseconds();

		u64 GetTimeMicroSeconds();

		u64 GetTimeNanoSeconds();

		/// 1 tick is 10ns, independent of processor speed
		u64 Ticks();

		u64 ProcessorTicks();

	private:

		static u64 GetTotalTicks();

	private:

		u64  startTick;
		u64  ticks;
		bool running;
		static const int TIMER_SPEED;
	};

	//-------------------------------------------------------------------------------------------------
	inline Timer::Timer() : ticks(0), running(true)
	{
		startTick = GetTotalTicks();
	}

	//-------------------------------------------------------------------------------------------------
	inline Timer::~Timer()
	{
		Stop();
	}

	//-------------------------------------------------------------------------------------------------
	inline void Timer::Stop()
	{
		if (!running)
			return;

		ticks = ProcessorTicks();
		running = false;
	}

	//-------------------------------------------------------------------------------------------------
	inline u64 Timer::GetTimeMilliseconds()
	{
		return ProcessorTicks() * 1000 / TIMER_SPEED;
	}

	//-------------------------------------------------------------------------------------------------
	inline u64 Timer::GetTimeMicroSeconds()
	{
		// 1000000 = 10^6
		return ProcessorTicks() * 1000000 / TIMER_SPEED;
	}

	//-------------------------------------------------------------------------------------------------
	inline u64 Timer::GetTimeNanoSeconds()
	{
		// 1000000000 = 10^9
		return ProcessorTicks() * 1000000000 / TIMER_SPEED;
	}

	//-------------------------------------------------------------------------------------------------
	inline u64 Timer::Ticks()
	{
		// 1 tick = 10ns
		return GetTimeNanoSeconds() / 10;
	}

	//-------------------------------------------------------------------------------------------------
	inline u64 Timer::ProcessorTicks()
	{
		if (running)
			ticks = GetTotalTicks() - startTick;

		return ticks;
	}
}