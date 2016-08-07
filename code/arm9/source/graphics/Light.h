#pragma once

#include "core/types.h"
#include "graphics/Color.h"
#include "util/Vec3.h"

namespace Graphics
{
	class Light
	{
	public:

		Light(Framework::Color color, Framework::Vector3 direction);

	public:

		Framework::Color Color;
		Framework::Vector3 Direction;
	};

	//-------------------------------------------------------------------------------------------------
	inline Light::Light(Framework::Color color, Framework::Vector3 direction) : Color(color), Direction(direction)
	{

	}
}