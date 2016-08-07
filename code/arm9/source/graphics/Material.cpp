#include "graphics/Material.h"

#include "graphics/BasicEffect.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	Material::Material()
	{
		AmbientLightColor = Color::Black;
		DiffuseColor = Color::White;
		EmissiveColor = Color::Black;
		SpecularColor = Color::Black;
		SpecularPower = 1.0f;
	}

	//-------------------------------------------------------------------------------------------------
	void Material::SetEffectParameters(BasicEffect &effect)
	{
		effect.AmbientLightColor = AmbientLightColor;
		effect.DiffuseColor      = DiffuseColor;
		effect.EmissiveColor     = EmissiveColor;
		effect.SpecularColor     = SpecularColor;
		effect.SpecularPower     = SpecularPower;
		effect.Texture           = Texture;
		effect.TextureEnabled    = (Texture != nullptr);
	}
}