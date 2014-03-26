#pragma once

#include "types.h"
#include "Vertex.h"
#include "DisplayList.h"

namespace Graphics
{
	class ModelMeshPart
	{
	public:

		ModelMeshPart();

		void Draw();

	public:

		Ptr<BasicEffect> Effect;
		List<Vertex> Vertices;
		List<u16> Indices;

		Ptr<Graphics::VertexBuffer> VertexBuffer;
		Ptr<Graphics::IndexBuffer>  IndexBuffer;

	private:

		bool displayListInitialized;
		DisplayList displayList;
	};
}