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

	public:

		int OriginX, OriginY;

		ObjPriority Priority;
		
		int Identifier;
		int ImageIndex;
		int ImageSpeed;
		ObjSize  size;
		ObjShape shape;
	};
}
