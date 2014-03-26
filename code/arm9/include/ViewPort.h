#pragma once

#include "types.h"
#include "fixed.h"

namespace Graphics
{
	struct ViewPort
	{
	public:

		///
		ViewPort();

		///
		ViewPort(int x, int y, int width, int height);

		///
		fx12 AspectRatio();

	public:

		int X, Y, Width, Height;
	};

	//-------------------------------------------------------------------------------------------------
	inline ViewPort::ViewPort() : X(0), Y(0), Width(1), Height(1)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline ViewPort::ViewPort(int x, int y, int width, int height) : X(x), Y(y), Width(width), Height(height)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline fx12 ViewPort::AspectRatio()
	{
		return fx12(Width) / Height;
	}
}