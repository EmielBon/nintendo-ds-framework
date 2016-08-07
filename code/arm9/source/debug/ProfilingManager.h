#pragma once

#include "core/types.h"
#include "ProfilingResult.h"
#include "util/MathFunctions.h"

namespace Debug
{
	class ProfilingManager
	{
	public:

		static void RefineResult(const String &name, int64 elapsedTicks);

	public:

		static Dictionary<String, ProfilingResult> ProfilingResults;
	};

}
