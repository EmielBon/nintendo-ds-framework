#pragma once

#include "core/types.h"

namespace Graphics
{
	class Texture
	{
	public:

		Texture();

		Texture(int width, int height);

		int GetByteSize() const;

	public:

		int Width, Height;
		List<u16> Pixels;
		Ptr<Graphics::Palette> Palette;
		
	private:
		
		int parameters;
	};

	//-------------------------------------------------------------------------------------------------
	inline Texture::Texture() : Width(0), Height(0), parameters(0)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline Texture::Texture(int width, int height) : Width(width), Height(height), parameters(0)
	{
		
	}

	//-------------------------------------------------------------------------------------------------
	inline int Texture::GetByteSize() const
	{
		return Pixels.size() * sizeof(u16);
	}
}