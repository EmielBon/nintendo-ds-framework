#include "util/StringHelper.h"
#include "util/MathFunctions.h"
#include "debug/Debug.h"

namespace Util
{
	//-------------------------------------------------------------------------------------------------
	List<String> StringHelper::Split(const String &str, char delimiter)
	{
		List<String> tokens;
		tokens.push_back("");

		for(u32 i = 0; i < str.length(); ++i)
		{
			String &token = tokens[tokens.size() - 1];
			char c = str[i];
			
			if (c == delimiter)
				tokens.push_back("");
			else if (c == '\0')
				break;
			else
				token += c;
		}

		return tokens;
	}

	//-------------------------------------------------------------------------------------------------
	String StringHelper::Replicate(const String &str, int amount)
	{
		std::stringstream ss;

		for(int i = 0; i < amount; ++i)
		{
			ss << str;
		}

		return ss.str();
	}

	//-------------------------------------------------------------------------------------------------
	bool StringHelper::HasPrefix(const String &source, const String &prefix)
	{
		if(prefix.length() > source.length())
			return false;
		return source.substr(0, prefix.length()) == prefix;
	}

	//-------------------------------------------------------------------------------------------------
	float StringHelper::ParseFloat(const String &str)
	{
		int l = str.length();
		float n = 0;
		int div = 0;
		int sign = 1;

		for(int i = 0; i < l; ++i)
		{
			char d = str[i];
			if (d == '-')
				sign = -1;
			else if (d == '.')
				div =  l - (i + 1);
			else
				n = 10 * n + ParseInt(d);
		}
		return n / Math::Pow(10, div) * sign;
	}

	//-------------------------------------------------------------------------------------------------
	int StringHelper::ParseInt(char c)
	{
		int d = c - '0';
		ASSERT(d >= 0 && d <= 9, "FUUUUUU");
		return d;
	}

	//-------------------------------------------------------------------------------------------------
	int StringHelper::ParseInt(const String &str)
	{
		int d = 0;
		bool neg = false;

		for(u32 i = 0; i < str.length(); ++i)
		{
			if (i == 0 && str[i] == '-')
			{
				neg = true;
				continue;
			}
			d = d * 10 + ParseInt(str[i]);
		}
		return (neg) ? -d : d;
	}

	//-------------------------------------------------------------------------------------------------
	bool StringHelper::ParseBool(const String &str)
	{
		ASSERT(str == "false" || str == "true", "FUUUUU");
		return str == "true";
	}

}
