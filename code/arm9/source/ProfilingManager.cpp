#include "ProfilingManager.h"

namespace Debug
{
	TreeMap<String, ProfilingResult> ProfilingManager::ProfilingResults;

	//-------------------------------------------------------------------------------------------------
	void ProfilingManager::RefineResult( const String &name, int64 elapsedTicks )
	{
		ProfilingResult& result = ProfilingResults[name];

		result.Name            = name;
		result.LastDuration    = elapsedTicks;
		result.TotalDuration  += elapsedTicks;
		result.LongestDuration = Math::Max(result.LongestDuration.Ticks(), elapsedTicks);
		result.N++;
	}
}