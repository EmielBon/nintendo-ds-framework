#include "debug/LogEntry.h"
#include "util/StringHelper.h"
#include <time.h>

namespace Debug
{
	//-------------------------------------------------------------------------------------------------
	String LogEntry::GetCurrentTime() const
	{
		// Adapted from RealTimeClock nds example in devkitPro
		int hours, seconds, minutes;

		time_t unixTime = time(NULL);
		struct tm* timeStruct = gmtime((const time_t *)&unixTime);

		hours   = timeStruct->tm_hour;
		minutes = timeStruct->tm_min;
		seconds = timeStruct->tm_sec;

		return ToStr((hours < 10 ? "0" : "") << hours << ":" << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds);
	}
}
