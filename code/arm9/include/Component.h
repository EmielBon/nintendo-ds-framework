#pragma once

#include "IUpdateable.h"
#include "IDrawable.h"
#include "types.h"
#include "Rectangle.h"

namespace GUI
{
	class Component : public Framework::IUpdateable, Framework::IDrawable
	{
	protected:

		Component();

		Component(int x, int y, int width, int height);

	public:

		bool Contains(int x, int y);

	public:

		Framework::Rectangle Bounds;
	};

	//-------------------------------------------------------------------------------------------------
	inline Component::Component() : Bounds(0, 0, 1, 1)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline Component::Component(int x, int y, int width, int height) : Bounds(x, y, width, height)
	{

	}
}