#pragma once

#include "core/types.h"
#include "graphics/Color.h"

namespace Graphics
{
	struct Material
	{
	public:

		Material();

		void SetEffectParameters(BasicEffect &effect);

	public:

		Color AmbientLightColor;
		Color DiffuseColor;
		Color EmissiveColor;
		Color SpecularColor;
		float SpecularPower;
		Ptr<Graphics::Texture> Texture;
	};
}