#pragma once

#include "types.h"
#include "SpriteSubImage.h"
#include <nds/arm9/sprite.h>
#include "fixed.h"

namespace Graphics
{
	class ObjectAttributeMemory;

	class Sprite
	{
		friend class ObjectAttributeMemory;

	public:

		/// Constructor
		Sprite(const List<SpriteSubImage> &subImages);

		/// Calculates the set of unique indices in this sprite, should be called after changing the SubImages property
		void ApplyChanges();

	public:

		int X, Y;
		int OriginX, OriginY;

		fx8 Scale;
		ObjPriority Priority;

		u32 SubImageIndex;
		int ImageSpeed;

		List<SpriteSubImage> SubImages;
		Set<u32> UniqueIndices; // Todo: also used in Maps, extract?

	protected:

		ObjSize  size;
		ObjShape shape;
	};
}