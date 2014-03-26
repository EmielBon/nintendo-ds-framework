#pragma once

#include "Vec2.h"
#include "Vec3.h"

namespace Graphics
{
	struct Vertex
	{
		Vector3 Position;
		Vector3 Normal;
		Vector2 TextureCoordinates;
	};

	struct VertexF
	{
		Vec3<float> Position;
		Vec3<float> Normal;
		Vec2<float> TextureCoordinates;
	};
}
