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

		virtual ~FileStream() { }

		/** \brief Opens this stream for reading.
		 *  \param path The path to the file in the file system. */
		void Open(const String &path);

		/** \brief Closes this stream */
		void Close();

		/** \brief Reads the file's header.
		 *  \bug When this method is not called directly after opening the stream, it will just read the next couple 
		 *       of bytes after the current file position and interpret those as the header. 
		 *  \todo Let the File class help with the header problem. 
		 *  \returns The header of the file as the template-specified type. */
		template<typename H>
		H ReadHeader();

		/** \brief Reads a number of elements from the stream.
		 *  \param elements The number of elements to read.
		 *  \returns A list of the read elements.
		 *
		 *  Reading starts at the current file position. The type specification determines the type (and size) of the 
		 *  elements. If reading goes beyond the end of the file, the list containing the elements up to the end of the
		 *  file is returned. */
		template<class T>
		Ptr<List<T>> Read(int elements);

		/** \brief Reads all remaining elements from the stream.
		 *  \returns A list of the read elements.
		 *
		 *  Reading starts at the current file position. The type specification determines the type (and size) of the 
		 * elements. */
		template<class T>
		Ptr<List<T>> ReadAll();

		/** \brief Reads raw bytes from the stream.
		 *  \param buffer A pointer to the memory in which the read data can be stored.
		 *  \param bytesPerElement The number of bytes that takes up 1 element.
		 *  \param nrOfElements The number of elements that will be read.
		 *  \returns The number of read elements.

		 *  Reading starts at the current file position. If reading goes beyond the end of the file, number of read 
		 *  elements up to the end of the file is returned. */
		int Read(void *buffer, u32 bytesPerElement, u32 nrOfElements);

		/** \brief Prints all directories in the root.
		 *  \param root A string to the root directory.
		 *  \todo Remove this function or integrate it properly with the console, instead of using printf.
		 *
		 *  For debug purposes. Copied from the libnds file system example. Uses printf for printing. */
		static void ListDirectories(const char *root);

	protected:

		bool open;
		FILE* stream;

	public:
		
		bool EndOfFile;
		String resourceName;
	};

	//-------------------------------------------------------------------------------------------------
	inline FileStream::FileStream(const String &resourceName) : stream(0), EndOfFile(false), resourceName(resourceName)
	{
	}

	//-------------------------------------------------------------------------------------------------
	template<typename H>
	inline H FileStream::ReadHeader()
	{
		H header;
		Read(&header, 1, sizeof(H));
		return header;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T> 
	inline Ptr<List<T>> FileStream::Read(int elements)
	{
		auto binaryData = New<List<T>>();

		for(int i = 0; i < elements; ++i)
		{
			T buffer;
			int elementsRead = Read(&buffer, sizeof(T), 1);
			if (elementsRead < 1)
			{
				EndOfFile = true;
				break;
			}
			binaryData->push_back(buffer);
		}

		return binaryData;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T> 
	inline Ptr<List<T>> FileStream::ReadAll()
	{
		const int bufferSize = Math::Max(8U, sizeof(T));

		auto binaryData = New<List<T>>();

		T buffer[bufferSize];
		int byterPerElement = sizeof(T);
		int nrOfElements = bufferSize;

		int elementsRead = Read(buffer, byterPerElement, nrOfElements);

		while(elementsRead > 0)
		{
			for(int i = 0; i < elementsRead; ++i)
				binaryData->push_back(buffer[i]);
			elementsRead = Read(buffer, byterPerElement, nrOfElements);
		}

		EndOfFile = true;
		return binaryData;
	}
}