#pragma once

#include "Size.h"
#include "types.h"
#include "Vec2.h"

namespace Framework
{
	struct Rectangle
	{
	public:

		Rectangle() = default;

		Rectangle(int x, int y, int width, int height);

	public:

		Framework::Point Position;
		::Size Size;
	};

	//-------------------------------------------------------------------------------------------------
	inline Rectangle::Rectangle(int x, int y, int width, int height) : Position(x, y), Size(width, height)
	{

	}
}