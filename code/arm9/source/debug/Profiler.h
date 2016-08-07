#pragma once

#include "core/types.h"
#include "system/Timer.h"
#include "ProfilingManager.h"

#define PROFILE_METHOD(name) Debug::Profiler profiler ## name(#name);

namespace Debug
{
	class Profiler
	{
	public:

		Profiler(const String &name);

		virtual ~Profiler();
		
		void Begin();

		void End();

		Ptr<Timer> GetTimer() const;

		String GetElapsedTimeAsString() const;

	private:

		String name;
		Ptr<Timer> timer;
	};

	//-------------------------------------------------------------------------------------------------
	inline Profiler::Profiler(const String &name) : name(name)
	{
		Begin();
	}

	//-------------------------------------------------------------------------------------------------
	inline Profiler::~Profiler()
	{
		End();
		ProfilingManager::RefineResult(name, timer->Ticks());
	}

	//-------------------------------------------------------------------------------------------------
	inline void Profiler::Begin()
	{
		timer = Timer::Start();
	}

	//-------------------------------------------------------------------------------------------------
	inline void Profiler::End()
	{
		timer->Stop();
	}

	//-------------------------------------------------------------------------------------------------
	inline Ptr<Timer> Profiler::GetTimer() const
	{
		return timer;
	}
}
