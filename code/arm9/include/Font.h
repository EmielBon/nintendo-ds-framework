#pragma once

#include "types.h"
#include "Size.h"
#include "TileSet.h"

namespace Graphics
{
	class Font : public TileSet
	{
	public:

		Font() = default;

		Framework::Size CharSize() { return tileSize; }

		int WidthForString(const String &str) { return str.length() * CharSize().Width; }

		String StringForWidth(const String &str, int width) { return str.substr(0, width / CharSize().Width); }
	};
}
