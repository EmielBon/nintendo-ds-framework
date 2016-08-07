#pragma once

#include "core/types.h"
#include "Color.h"
#include "Mat.h"
#include "Texture.h"
#include "DirectionalLight.h"

namespace Graphics
{
	class BasicEffect
	{
	public:

		BasicEffect();

		void Apply();

	private:

		int TextureSizeParameter(int size);

		void SynchronizeLight(const DirectionalLight &light);
		
	public:

		float Alpha;
		Color AmbientLightColor;
		Color DiffuseColor;
		DirectionalLight DirectionalLight0;
		DirectionalLight DirectionalLight1;
		DirectionalLight DirectionalLight2;
		DirectionalLight DirectionalLight3;
		Color EmissiveColor;
		Color FogColor;
		bool FogEnabled;
		float FogStart;
		float FogEnd;
		bool LightingEnabled;
		Matrix Projection;
		Color SpecularColor;
		float SpecularPower;
		Ptr<Graphics::Texture> Texture;
		bool TextureEnabled;
		bool VertexColorEnabled;
		Matrix View;
		Matrix World;
	};
}