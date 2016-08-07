#pragma once

#include "debug/Log.h"
#include "debug/LogPrinter.h"
#include "util/StringHelper.h"

namespace Debug
{
	extern Log StandardLog;
}

#ifdef DEBUG

#define LOG_ENABLE()\
{\
	Debug::StandardLog.Enable();\
}

#define LOG_DISABLE()\
{\
	Debug::StandardLog.Disable();\
}

#define LOG_START(expression)\
{\
	Debug::StandardLog.StartEntry(ToStr(expression));\
}

#define LOG_END()\
{\
	Debug::StandardLog.EndEntry();\
	Debug::LogPrinter::Print(Debug::StandardLog);\
}

#define LOG_CANCEL()\
{\
	Debug::StandardLog.CancelEntry();\
}

#define LOG(expression)\
{\
	Debug::StandardLog.PutMessage(ToStr(expression));\
	Debug::LogPrinter::Print(Debug::StandardLog);\
}

#define LOG_ERROR(expression)\
{\
	Debug::StandardLog.PutError(ToStr(expression));\
	Debug::LogPrinter::Print(Debug::StandardLog);\
}

#define LOG_WARNING(expression)\
{\
	Debug::StandardLog.PutWarning(ToStr(expression));\
	Debug::LogPrinter::Print(Debug::StandardLog);\
}

#define LOG_CLEAR()\
{\
	Debug::StandardLog.Clear();\
	Debug::LogPrinter::Clear();\
}

#else

#define LOG_ENABLE()
#define LOG_DISABLE()
#define LOG_START(expression)
#define LOG_END()
#define LOG_CANCEL()
#define LOG(expression)
#define LOG_ERROR(expression)
#define LOG_WARNING(expression) 
#define LOG_CLEAR()

#endif
