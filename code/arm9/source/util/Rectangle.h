#pragma once

#include "util/Size.h"
#include "core/types.h"
#include "util/Vec2.h"

namespace Framework
{
	struct Rectangle
	{
	public:

		Rectangle() = default;

		Rectangle(int x, int y, int width, int height);

	public:

		Framework::Point Position;
		Framework::Size  Size;
	};

	//-------------------------------------------------------------------------------------------------
	inline Rectangle::Rectangle(int x, int y, int width, int height) : Position(x, y), Size(width, height)
	{

	}
}
