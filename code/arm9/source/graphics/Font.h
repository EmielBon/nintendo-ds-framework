#pragma once

#include "graphics/TileSet16.h"
#include "core/types.h"
#include "util/Size.h"

namespace Graphics
{
	class Font : public TileSet16
	{
	public:

		Font() = default;

		Framework::Size CharSize() { return tileSize; }

		int WidthForString(const String &str) { return str.length() * CharSize().Width; }

		String StringForWidth(const String &str, int width) { return str.substr(0, width / CharSize().Width); }
	};
}