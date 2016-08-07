#pragma once

#include "core/types.h"
#include "graphics/Vertex.h"
#include "graphics/DisplayList.h"

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