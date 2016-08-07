#pragma once

#include "../core/types.h"

// Converts an expression to a String. 
// Example: ToStr("I am " << 8 << " years old");
#define ToStr(expr) ((static_cast<std::stringstream*>(&(std::stringstream() << expr)))->str())

namespace Util
{
	class StringHelper
	{
	public:

		static List<String> Split(const String &str, char delimiter);

		static String Replicate(const String &str, int amount);

		static bool HasPrefix(const String &source, const String &prefix);

		//static String ToString(char c);

		static float ParseFloat(const String &str);

		static int ParseInt(char c);

		static int ParseInt(const String &str);

		static bool ParseBool(const String &str);
	};
}
