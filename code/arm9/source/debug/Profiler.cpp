#include "Profiler.h"
#include "util/StringHelper.h"

namespace Debug
{
	//-------------------------------------------------------------------------------------------------
	String Profiler::GetElapsedTimeAsString() const
	{
		u32 msec = timer->GetTimeMilliseconds();
		u32 usec = timer->GetTimeMicroSeconds();
		u32 time = (msec > 0) ? msec : usec;

		return ToStr(time << (time == msec ? "ms" : "us"));
	}
}
