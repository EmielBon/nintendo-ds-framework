#pragma once

#include "types.h"

namespace Graphics
{
	class SpriteSet
	{
	public:

		Dictionary<String, Ptr<Sprite>> Sprites;

		Ptr<Sprite>& operator[](const String &key)
		{
			return at(key);
		}

		Ptr<Sprite>& at(const String &key)
		{
			return Sprites.at(key);
		}
	};
}