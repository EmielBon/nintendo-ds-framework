#pragma once

#include "types.h"
#include "ProfilingResult.h"
#include "MathFunctions.h"

namespace Debug
{
	class ProfilingManager
	{
	public:

		static void RefineResult(const String &name, int64 elapsedTicks);

	public:

		static TreeMap<String, ProfilingResult> ProfilingResults;
	};

}