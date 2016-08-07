#include "util/TimeSpan.h"
#include "debug/Assert.h"

namespace System
{
	const TimeSpan TimeSpan::Zero;

	//-------------------------------------------------------------------------------------------------
	int64 TimeSpan::CalculateTicks(int days, int hours, int minutes, int seconds, int milliseconds)
	{
		// there's no overflow checks for hours, minutes, ...
		// so big hours/minutes values can overflow at some point and change expected values
		int hrssec = (hours * 3600); // break point at (Int32.MaxValue - 596523)
		int minsec = (minutes * 60);
		int64 t = ((int64)(hrssec + minsec + seconds) * 1000L + (int64)milliseconds);
		t *= 10000;

		int64 result = 0;

		bool overflow = false;
		// days is problematic because it can overflow but that overflow can be 
		// "legal" (i.e. temporary) (e.g. if other parameters are negative) or 
		// illegal (e.g. sign change).
		if (days > 0) {
			int64 td = TicksPerDay * days;
			if (t < 0) {
				int64 ticks = t;
				t += td;
				// positive days -> total ticks should be lower
				overflow = (ticks > t);
			}
			else {
				t += td;
				// positive + positive != negative result
				overflow = (t < 0);
			}
		}
		else if (days < 0) {
			int64 td = TicksPerDay * days;
			if (t <= 0) {
				t += td;
				// negative + negative != positive result
				overflow = (t > 0);
			}
			else {
				int64 ticks = t;
				t += td;
				// negative days -> total ticks should be lower
				overflow = (t > ticks);
			}
		}

		ASSERT(!overflow, "Overflow");

		result = t;
		return result;
	}
}