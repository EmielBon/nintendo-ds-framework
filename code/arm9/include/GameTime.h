#pragma once

#include "TimeSpan.h"

namespace Framework
{
	class GameTime
	{
	public:

		GameTime();

		virtual ~GameTime() { }

		GameTime(System::TimeSpan totalRealTime, System::TimeSpan elapsedRealTime, System::TimeSpan totalGameTime, System::TimeSpan elapsedGameTime, bool isRunningSlowly = false);

	public: 

		System::TimeSpan ElapsedGameTime;
		System::TimeSpan ElapsedRealTime;
		bool IsRunningSlowly;
		System::TimeSpan TotalGameTime;
		System::TimeSpan TotalRealTime;
	};
	
	//-------------------------------------------------------------------------------------------------
	inline GameTime::GameTime() : IsRunningSlowly(false)
	{

	}
}