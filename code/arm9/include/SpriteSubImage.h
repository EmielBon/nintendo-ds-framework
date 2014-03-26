#pragma once

#include "types.h"

namespace Graphics
{
	// todo: rename
	class SpriteSubImage
	{
	public:

		SpriteSubImage();

		SpriteSubImage(int width, int height);

		int TileCount() const;

		u32 GfxIndex() const;

	public:

		const int Width, Height;
		List<u32> TileIdentifiers;
	};

	//-------------------------------------------------------------------------------------------------
	inline SpriteSubImage::SpriteSubImage() : Width(0), Height(0)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline SpriteSubImage::SpriteSubImage(int width, int height) : Width(width), Height(height)
	{
		TileIdentifiers.assign(width * height, 0);
	}

	//-------------------------------------------------------------------------------------------------
	inline int SpriteSubImage::TileCount() const
	{
		return Width * Height;
	}

	//-------------------------------------------------------------------------------------------------
	inline u32 SpriteSubImage::GfxIndex() const
	{
		return TileIdentifiers[0];
	}
}