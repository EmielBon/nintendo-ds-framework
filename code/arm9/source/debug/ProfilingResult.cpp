#include "debug/ProfilingResult.h"
#include "debug/Profiler.h"
#include <cstdio>

namespace Debug
{
	//-------------------------------------------------------------------------------------------------
	String ProfilingResult::ToString() const
	{
		char str[100];
		
		float current = LastDuration.TotalMilliseconds();
		float average = AverageDuration().TotalMilliseconds();
		float maximum = LongestDuration.TotalMilliseconds();

		sprintf(str, "%s: c=%.3f %c=%.3f m=%.3f", Name.c_str(), current, (char)230, average, maximum);
		
		return String(str);
	}
}