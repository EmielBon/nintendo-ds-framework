#pragma once

#include "core/types.h"
#include "graphics/TiledImage.h"
#include <nds/arm9/sprite.h>
#include "core/fixed.h"

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

		int OriginX, OriginY;

		ObjPriority Priority;
		
		int ImageIndex;
		int ImageSpeed;

		List<TiledImage> SubImages;
		
	protected:

		ObjSize  size;
		ObjShape shape;
	};
}