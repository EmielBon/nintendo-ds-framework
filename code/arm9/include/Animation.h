#pragma once

#include "types.h"
#include "TileSet.h"
#include <memory>

namespace Graphics 
{
	class AnimationData
	{
	private:

		UniquePtr<TileSet> tileSet;
		Dictionary<String, List<int>> animations;
	};
}
