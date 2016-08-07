#pragma once

#include "debug/Log.h"

namespace Debug
{
	class LogPrinter
	{
	public:

		static void Print(Log &log);

		static void Clear();

		static bool HasLog(const Log &log);

//	private:

		static void Print(const LogEntry &entry, int depth);

	private:

		static Log *currentLog;
		static u32  oldLogSize;
	};

	//-------------------------------------------------------------------------------------------------
	inline bool LogPrinter::HasLog(const Log &log)
	{
		return (currentLog == &log);
	}
}