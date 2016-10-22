#pragma once

#include "TiledImage.h"

namespace Graphics
{

	struct Sprite
	{
		Sprite() : Identifier(0), Shape(OBJSHAPE_FORBIDDEN), Size(OBJSIZE_8)
		{

		}

		Sprite(int identifier, ObjShape shape, ObjSize size) : Identifier(identifier), Shape(shape), Size(size) 
		{
		
		}

		int Identifier;
		ObjShape Shape;
		ObjSize Size;
	};

	using SpriteSet = Dictionary<String, List<Sprite*>>;

}
