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

}
