/** 
 * \class MapResource
 * \brief A Nintendo DS internal map
 */

#pragma once

#include "IGraphicsResource.h"
#include "types.h"
#include "ScreenBlockEntry.h"

namespace LLR
{
	class MapResource : public IGraphicsResource
	{
	public:

		MapResource(int size);

		MapResource(int width, int height);

		Graphics::ScreenBlockEntry& operator[] (int index);

		int ByteSize() const;

	public:

		List<Graphics::ScreenBlockEntry> ScreenBlockEntries;
	};

	//-------------------------------------------------------------------------------------------------
	inline MapResource::MapResource(int size)
	{
		ScreenBlockEntries.resize(size);
	}

	//-------------------------------------------------------------------------------------------------
	inline MapResource::MapResource(int width, int height)
	{
		ScreenBlockEntries.resize(width * height);
	}

	//-------------------------------------------------------------------------------------------------
	inline Graphics::ScreenBlockEntry& MapResource::operator[] (int index)
	{
		return ScreenBlockEntries[index];
	}

	//-------------------------------------------------------------------------------------------------
	inline int MapResource::ByteSize() const
	{
		return ScreenBlockEntries.size() * sizeof(Graphics::ScreenBlockEntry);
	}
}