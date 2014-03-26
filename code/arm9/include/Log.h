#pragma once

#include "types.h"
#include "LogEntry.h"

namespace Debug
{
	class Log
	{
	public:
		
		Log();

		// Enable this log so logging calls can be made
		void Enable();

		// Disable this log until it is enabled again. Logging calls will be ignored.
		void Disable();

		// Returns whether this log accepts messages
		bool IsEnabled() const;

		void PutError(const String &message);

		void PutMessage(const String &message);
		
		void PutWarning(const String &message);

		void StartEntry(const String &message);

		void EndEntry();

		void CancelEntry();

		void Clear();

		LogEntry& Last();

		bool HasActiveEntry() const;

		LogEntry* GetActiveEntry();

	private:

		LogEntry* PutEntry(const LogEntry& entry);

		LogEntry* PutEntry(LogEntryType type, const String &title);

	private:

		Stack<LogEntry*> activeEntryStack;

	public:

		bool enabled;
		List<LogEntry> Entries;
	};

	//-------------------------------------------------------------------------------------------------
	inline Log::Log()
	{
		Enable();
	}

	//-------------------------------------------------------------------------------------------------
	inline void Log::Enable()
	{
		enabled = true;
	}

	//-------------------------------------------------------------------------------------------------
	inline void Log::Disable()
	{
		enabled = false;
	}

	//-------------------------------------------------------------------------------------------------
	inline bool Log::IsEnabled() const
	{
		return enabled;
	}

	//-------------------------------------------------------------------------------------------------
	inline void Log::PutError(const String &message)
	{
		PutEntry(LogEntryType::Error, message);
	}

	//-------------------------------------------------------------------------------------------------
	inline void Log::PutMessage(const String &message)
	{
		PutEntry(LogEntryType::Message, message);
	}

	//-------------------------------------------------------------------------------------------------
	inline void Log::PutWarning(const String &message)
	{
		PutEntry(LogEntryType::Warning, message);
	}

	//-------------------------------------------------------------------------------------------------
	inline void Log::CancelEntry()
	{
		EndEntry();
		Entries.pop_back();
	}

	//-------------------------------------------------------------------------------------------------
	inline LogEntry& Log::Last()
	{
		return Entries.back();
	}

	//-------------------------------------------------------------------------------------------------
	inline bool Log::HasActiveEntry() const
	{
		return !activeEntryStack.empty();
	}

	//-------------------------------------------------------------------------------------------------
	inline LogEntry* Log::PutEntry(LogEntryType type, const String &message)
	{
		return PutEntry( LogEntry(type, message) );
	}
}