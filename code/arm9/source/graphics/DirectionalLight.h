#pragma once

#include "core/types.h"
#include "Debug.h"
#include "Vec3.h"

namespace Graphics
{
	class DirectionalLight
	{
	public:

		DirectionalLight();

		DirectionalLight(int id, int statusbit, u16 color = 0);

	public:

		int Id;
		int StatusBit;
		bool Enabled;
		Vector3 Direction;
		u16 DiffuseColor;
		u16 SpecularColor;
	};

	//-------------------------------------------------------------------------------------------------
	inline DirectionalLight::DirectionalLight() : Id(0), StatusBit(0), Enabled(false), DiffuseColor(0), SpecularColor(0)
	{
		
	}

	//-------------------------------------------------------------------------------------------------
	inline DirectionalLight::DirectionalLight( int id, int statusbit, u16 color ) : Id(id), StatusBit(statusbit), Enabled(false), DiffuseColor(color), SpecularColor(0)
	{
		ASSERT(id >= 0 && id < 4, "Error: Invalid light id");
	}
}