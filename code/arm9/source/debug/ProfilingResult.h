#pragma once

#include "util/TimeSpan.h"

namespace Debug
{
	struct ProfilingResult
	{
	public:

		ProfilingResult();

		System::TimeSpan AverageDuration() const;

		String ToString() const;

	public:

		String Name;
		System::TimeSpan TotalDuration;
		System::TimeSpan LongestDuration;
		System::TimeSpan LastDuration;
		int N;
	};

	//-------------------------------------------------------------------------------------------------
	inline ProfilingResult::ProfilingResult() : N(0)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline System::TimeSpan ProfilingResult::AverageDuration() const
	{
		return TotalDuration.Ticks() / N;
	}

}
