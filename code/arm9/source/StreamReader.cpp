#include "StreamReader.h"

namespace FileSystem
{
	//-------------------------------------------------------------------------------------------------
	String StreamReader::ReadLine()
	{
		String line;
		char c = ReadChar();

		while (c != 0 && c != '\n') {

			if (c == '\r') {
				continue;
			}

			line += c;
			c = ReadChar();
		}

		return line;
	}

	//-------------------------------------------------------------------------------------------------
	u8 StreamReader::ReadChar()
	{
		uint8_t character;
		int elementsRead = fileStream.Read(&character);
		if (elementsRead < 1) {
			return 0;
		}
		return character;
	}

	//-------------------------------------------------------------------------------------------------
	List<String> StreamReader::ReadToEnd()
	{
		List<String> lines;

		auto characters = fileStream.ReadAll<uint8_t>();

		if (characters.empty()) {
			return lines;
		}

		String line;

		for (uint8_t c : characters) {

			if (c == '\r') {
				continue;
			}

			if (c == '\n') {
				lines.push_back(line);
				line = "";
				continue;
			}

			line += c;
		}

		lines.push_back(line);

		Close();

		return lines;
	}
}
