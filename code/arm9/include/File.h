/** 
 * \class File
 * \brief Represents a file in the file system 
 */

#pragma once

#include "types.h"

namespace FileSystem
{
	class File
	{
	protected:

		/* \brief Creates an instance of File.
		 * \param path Path to the file in the file system. */ 
		File(const String &path);

	public:

		virtual ~File() { }

		/* \brief Get the path to this file in the file system.
		 * \returns The path to this file in the file system as a string. */
		String GetPath() const;

	protected:

		String filePath;
	};

	//-------------------------------------------------------------------------------------------------
	inline File::File(const String &path) : filePath(path)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline String File::GetPath() const
	{
		return filePath;
	}
}