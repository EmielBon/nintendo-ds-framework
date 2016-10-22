#pragma once

#include "types.h"
#include "FileStream.h"
#include "Profiler.h"

namespace Framework
{
	// todo: add profiling for resource size in bytes, 4MB of memory is a lot but not infinite
	class ContentManager
	{
	public:

		/// Load a specific resource from the file with the specified name
		template<class T>
		static UniquePtr<T> Load(const String &name);

	private:

		/// Load the file's data
		template<class T>
		static UniquePtr<T> LoadResourceFromStream(FileSystem::FileStream &fs);
	};

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline UniquePtr<T> ContentManager::Load(const String &name)
	{
		using namespace FileSystem;

		String path = "/" + name + ".bin";

		FileStream fs(name);
		fs.Open(path);
		auto resource = LoadResourceFromStream<T>(fs);
		fs.Close();

		return resource;
	}
}
