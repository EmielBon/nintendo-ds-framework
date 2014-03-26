#include "LogPrinter.h"
#include "StringHelper.h"
#include "Game.h"
#include "Console.h"
#include "DebugUI.h"

namespace Debug
{
	Log* LogPrinter::currentLog = NULL;
	u32  LogPrinter::oldLogSize = 0;
	
	using namespace Util;
	using namespace Debug;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	void LogPrinter::Print(Log &log)
	{
		// Postpone printing if there is an open log entry still being edited
		if (log.HasActiveEntry())
			return;

		if (!HasLog(log))
		{
			currentLog = &log;
			oldLogSize = 0;
		}

		auto &entries = currentLog->Entries;

		for(u32 i = oldLogSize; i < entries.size(); ++i)
		{
			Print(entries[i], 0);
		}

		oldLogSize = entries.size();
	}

	//-------------------------------------------------------------------------------------------------
	void LogPrinter::Clear()
	{
		oldLogSize = 0;
		DebugUI::Console->Clear();
	}

	//-------------------------------------------------------------------------------------------------
	void LogPrinter::Print(const LogEntry &entry, int depth)
	{
		String prefix = "";
		int indentAmount = 1;
		//char x[] = {'-', 7, 9}; 

		if (depth > 0)
		{
			char enumerationToken = entry.HasSubEntries() ? '-' : '|';
			String indent = StringHelper::Replicate("| ", (depth - 1) * indentAmount);
			prefix = indent + ToStr(enumerationToken) + " ";
		}

		DebugUI::Console->WriteLine(prefix + entry.Title);

		auto &entries = entry.SubEntries;

		for(auto it = entries.begin(); it != entries.end(); ++it)
		{
			Print(*it, depth + 1);
		}
	}
}