#include "GameTime.h"

namespace Framework
{
	using namespace System;

	//-------------------------------------------------------------------------------------------------
	GameTime::GameTime(TimeSpan totalRealTime, TimeSpan elapsedRealTime, TimeSpan totalGameTime, TimeSpan elapsedGameTime, bool isRunningSlowly /* = false */)
	{
		TotalRealTime = totalRealTime;
		ElapsedRealTime = elapsedRealTime;
		TotalGameTime = totalGameTime;
		ElapsedGameTime = elapsedGameTime;
		IsRunningSlowly = isRunningSlowly;
	}
}