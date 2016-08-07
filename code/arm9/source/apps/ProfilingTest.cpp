#include "ProfilingTest.h"

#include "Debug.h"

namespace Test
{
	using namespace Debug;

	//-------------------------------------------------------------------------------------------------
	void ProfilingTest::Initialize()
	{
		counter = 0;

		auto methodTimer = Timer::Start();
		
		DoSomeWork(1000);

		auto statementTimer = Timer::Start();
		DoSomeWork(10000);
		statementTimer->Stop();
		
		DoSomeWork(1000);

		methodTimer->Stop();

		u64 methodTime = methodTimer->GetTimeNanoSeconds();
		u64 statementTime = statementTimer->GetTimeNanoSeconds();

		CRASH("Counter: " << counter << " | Method: " << methodTime << " | Statement: " << statementTime << " | Percentage: " << statementTime * 100 / methodTime);
	}

	//-------------------------------------------------------------------------------------------------
	void ProfilingTest::DoSomeWork(int i)
	{
		int j = 0;
		
		while(true)
		{
			counter++;
			j++;
			if (j >= i)
				break;
		}
	}

}