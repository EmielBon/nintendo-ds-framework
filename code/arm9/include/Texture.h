#pragma once

#include "types.h"

namespace Graphics
{
	class Texture
	{
	public:

		Texture();

		Texture(int width, int height, const uint16_t *data = nullptr);

		int GetByteSize() const;

	public:

		int Width, Height;
		List<uint16_t> Pixels;
		Ptr<Graphics::Palette> Palette;
		
	private:
		
		int parameters;
	};

	//-------------------------------------------------------------------------------------------------
	inline Texture::Texture() : Width(0), Height(0), parameters(0)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline Texture::Texture(int width, int height, const uint16_t *data /* = nullptr */) : Width(width), Height(height), parameters(0)
	{
		if (data) {
			size_t size = width * height;
			Pixels.assign(data, data + size);
		}
	}

	//-------------------------------------------------------------------------------------------------
	inline int Texture::GetByteSize() const
	{
		return Pixels.size() * sizeof(u16);
	}
}
