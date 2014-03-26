#include "Log.h"
#include "Assert.h"

namespace Debug
{
	Stack<LogEntry*> activeEntryStack;

	//-------------------------------------------------------------------------------------------------
	LogEntry* Log::PutEntry(const LogEntry& entry)
	{
		if (!IsEnabled())
			return NULL;

		if (activeEntryStack.empty())
		{
			Entries.push_back(entry);
			return &Last();
		}
		else
		{
			LogEntry* activeEntry = GetActiveEntry();
			activeEntry->AddSubEntry(entry);
			return &activeEntry->Last();
		}
	}

	//-------------------------------------------------------------------------------------------------
	void Log::StartEntry(const String &message)
	{
		if (!IsEnabled())
			return;

		LogEntry* entry = PutEntry(LogEntryType::Message, message);
		activeEntryStack.push(entry);
	}

	//-------------------------------------------------------------------------------------------------
	void Log::EndEntry()
	{
		if (!IsEnabled())
			return;

		ASSERT(!activeEntryStack.empty(), "Unbalanced start/end statements for logging: EndEntry() called while activeEntryStack was empty");
		activeEntryStack.pop();
	}

	//-------------------------------------------------------------------------------------------------
	void Log::Clear()
	{
		while( HasActiveEntry() )
			activeEntryStack.pop();
		Entries.clear();
	}

	//-------------------------------------------------------------------------------------------------
	LogEntry* Log::GetActiveEntry()
	{
		if ( activeEntryStack.empty() )
			return NULL;
		return activeEntryStack.top();
	}
}