#pragma once

#include "types.h"
#include "Size.h"

namespace Framework2D
{
	class CollisionMap
	{
	public:

		/// Constructor
		CollisionMap(int width = 0, int height = 0);

		///
		bool Collision(int x, int y) const;

	private:

		///
		int GetTileFor(int x, int y) const;

	public:

		List<u8> Colors;
		const ::Size Size;
	};

	//-------------------------------------------------------------------------------------------------
	inline CollisionMap::CollisionMap(int width, int height) : Size(width, height)
	{
	}
}