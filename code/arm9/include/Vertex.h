#pragma once

#include "Vec2.h"
#include "Vec3.h"

namespace Graphics
{
	struct VertexF
	{
		Vec3<float> Position;
		Vec3<float> Normal;
		Vec2<float> TextureCoordinates;
	};

	struct Vertex
	{
	public:

		Vertex() = default;

		explicit Vertex(const VertexF &v)
		{
			Position = (Vector3)(v.Position);
			Normal = (Vector3)(v.Normal);
			TextureCoordinates = (Vector2)(v.TextureCoordinates);
		}

	public:

		Vector3 Position;
		Vector3 Normal;
		Vector2 TextureCoordinates;
	};
}
