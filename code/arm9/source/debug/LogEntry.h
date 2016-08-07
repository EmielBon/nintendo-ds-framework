#pragma once

#include "core/types.h"

namespace Debug
{
	enum LogEntryType
	{
		Message,
		Warning,
		Error,
	};

	struct LogEntry
	{
		friend class Log;

	public:

		LogEntry(const String &title);

		LogEntry(const LogEntryType &type, const String &title);

		void AddSubEntry(const LogEntry &entry);

		bool HasSubEntries() const;

		LogEntry& Last();

	private:

		String GetCurrentTime() const;

	public:

		List<LogEntry> SubEntries;
		LogEntryType Type;
		String Title;
		String TimeStamp;
	};

	//-------------------------------------------------------------------------------------------------
	inline LogEntry::LogEntry(const String &title) : LogEntry(LogEntryType::Message, title)
	{
		
	}

	//-------------------------------------------------------------------------------------------------
	inline LogEntry::LogEntry(const LogEntryType &type, const String &title) : Type(type), Title(title)
	{
		TimeStamp = GetCurrentTime();
	}

	//-------------------------------------------------------------------------------------------------
	inline void LogEntry::AddSubEntry(const LogEntry &entry)
	{
		SubEntries.push_back(entry);
	}

	//-------------------------------------------------------------------------------------------------
	inline bool LogEntry::HasSubEntries() const
	{
		return (SubEntries.size() > 0);
	}

	//-------------------------------------------------------------------------------------------------
	inline LogEntry& LogEntry::Last()
	{
		return SubEntries.back();
	}
}
