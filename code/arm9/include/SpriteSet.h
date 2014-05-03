#pragma once

#include "types.h"

namespace Graphics
{
	class SpriteSet
	{
	public:

		TreeMap<String, Ptr<Sprite>> Sprites;

		Ptr<Sprite>& operator[](const String &key)
		{
			return Sprites.at(key);
		}
	};
}