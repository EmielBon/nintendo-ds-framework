#pragma once

#include "types.h"
#include "TiledImage.h"
#include <nds/arm9/sprite.h>
#include "fixed.h"

namespace Graphics
{
	class ObjectAttributeMemory;

	class Sprite
	{
		friend class ObjectAttributeMemory;

	public:

		Sprite() = default;

		/// Constructor
		Sprite(const List<TiledImage> &subImages);

	public:

		int X, Y;
		int OriginX, OriginY;

		fx8 Scale;
		ObjPriority Priority;

		u32 SubImageIndex;
		int ImageSpeed;

		List<TiledImage> SubImages;
		
	protected:

		ObjSize  size;
		ObjShape shape;
	};
}