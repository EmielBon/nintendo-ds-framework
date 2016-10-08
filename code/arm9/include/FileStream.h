/** 
 * \class FileStream
 * \brief Provides functionality for reading files as a stream 
 */

#pragma once

#include "types.h"
#include <stdio.h>
#include "MathFunctions.h"

namespace FileSystem
{
	class FileStream
	{
	public:

		/** \brief Creates an empty closed stream. */
		FileStream(const String &resourceName);

		virtual ~FileStream() = default;

		/** \brief Opens this stream for reading.
		 *  \param path The path to the file in the file system. */
		void Open(const String &path);

		///
		size_t FileSize() const;

		/** \brief Closes this stream */
		void Close();

		/** \brief Reads all remaining elements from the stream.
		 *  \returns A list of the read elements.
		 *
		 *  Reading starts at the current file position. The type specification determines the type (and size) of the 
		 * elements. */
		template<class T>
		List<T> ReadAll();

		template<class T>
		List<T> Read(size_t numberOfElements);

		/** \brief Reads raw bytes from the stream.
		 *  \param buffer A pointer to the memory in which the read data can be stored.
		 *  \param bytesPerElement The number of bytes that takes up 1 element.
		 *  \param nrOfElements The number of elements that will be read.
		 *  \returns The number of read elements.

		 *  Reading starts at the current file position. If reading goes beyond the end of the file, number of read 
		 *  elements up to the end of the file is returned. */
		size_t Read(void *buffer, size_t bytesPerElement, size_t nrOfElements);

		template<class T>
		size_t Read(T *output);

		template<class T>
		size_t Read(T *output, size_t numberOfElements);

		/** \brief Prints all directories in the root.
		 *  \param root A string to the root directory.
		 *  \todo Remove this function or integrate it properly with the console, instead of using printf.
		 *
		 *  For debug purposes. Copied from the libnds file system example. Uses printf for printing. */
		static void ListDirectories(const char *root);

	protected:

		bool open;
		FILE* stream;
		size_t fileSize;

	public:
		
		String resourceName;
	};

	//-------------------------------------------------------------------------------------------------
	inline FileStream::FileStream(const String &resourceName) : open(false), stream(nullptr), fileSize(-1), resourceName(resourceName)
	{
	}

	//-------------------------------------------------------------------------------------------------
	inline size_t FileStream::FileSize() const
	{
		return fileSize;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	List<T> FileStream::ReadAll()
	{
		size_t elementSize = sizeof(T);
		size_t remainingBytes = fileSize - ftell(stream);
		size_t remainingElements = remainingBytes / elementSize;
		List<T> elements = Read<T>(remainingElements);
		sassert(elements.size() == remainingElements, "Error: File not fully read");
		Close();
		return elements;
	}

	template<class T>
	List<T> FileStream::Read(size_t numberOfElements)
	{
		List<T> elements(numberOfElements);
		size_t elementsRead = Read(elements.data(), sizeof(T), numberOfElements);
		elements.resize(elementsRead);
		return elements;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline size_t FileStream::Read(T *output)
	{
		return Read(output, 1);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline size_t FileStream::Read(T *output, size_t numberOfElements)
	{
		return Read(output, sizeof(T), numberOfElements);
	}
}
