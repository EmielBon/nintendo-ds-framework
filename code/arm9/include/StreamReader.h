#pragma once

#include "types.h"
#include "FileStream.h"

namespace FileSystem
{
	class StreamReader
	{
	public:

		StreamReader(const String &fileName);

		StreamReader(const FileStream &stream);

		virtual ~StreamReader() = default;

		void Close();

		String ReadLine();

		u8 ReadChar();

		List<String> ReadToEnd();

	private:

		FileStream fileStream;
	};

	//-------------------------------------------------------------------------------------------------
	inline StreamReader::StreamReader(const String &fileName) : fileStream(fileName)
	{
		fileStream.Open(fileName);
	}

	//-------------------------------------------------------------------------------------------------
	inline StreamReader::StreamReader(const FileStream &stream) : fileStream(stream)
	{
	}

	//-------------------------------------------------------------------------------------------------
	inline void StreamReader::StreamReader::Close()
	{
		fileStream.Close();
	}

	//-------------------------------------------------------------------------------------------------
	inline String StreamReader::ReadLine()
	{
		String line;

		while(!fileStream.EndOfFile)
		{
			char c = ReadChar();

			if (c == '\r')
				continue;
			if (c == '\n')
				break;

			line += c;
		}
		
		return line;
	}

	//-------------------------------------------------------------------------------------------------
	u8 StreamReader::ReadChar()
	{
		if (!fileStream.EndOfFile)
		{
			auto chars = fileStream.Read<u8>(1);
			if (chars.empty())
				return 0;
			return chars[0];
		}
		return 0;
	}

	//-------------------------------------------------------------------------------------------------
	List<String> StreamReader::ReadToEnd()
	{
		List<String> lines;

		while(!fileStream.EndOfFile)
		{
			lines.push_back( ReadLine() );
		}

		Close();

		return lines;
	}

}