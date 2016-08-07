#pragma once

#include "core/types.h"
#include "system/FileStream.h"
#include "debug/Profiler.h"

namespace Framework
{
	// todo: add profiling for resource size in bytes, 4MB of memory is a lot but not infinite
	class ContentManager
	{
	public:

		/// Load a specific resource from the file with the specified name
		template<class T>
		static Ptr<T> Load(const String &name);

	private:

		/// Load the file's data
		template<class T>
		static Ptr<T> LoadResourceFromStream(FileSystem::FileStream &fs);
	};

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Ptr<T> ContentManager::Load(const String &name)
	{
		using namespace FileSystem;

		// Caching
		static Dictionary<String, Ptr<T>> loadedContent;
		if (loadedContent.find(name) != loadedContent.end())
			return loadedContent[name];

		String path = "/" + name + ".bin";

		FileStream fs(name);
		fs.Open(path);
		auto resource = LoadResourceFromStream<T>(fs);
		fs.Close();

		loadedContent[name] = resource;

		return resource;
	}
}