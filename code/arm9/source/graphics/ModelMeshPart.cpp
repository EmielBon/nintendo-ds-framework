#include "graphics/ModelMeshPart.h"
#include "graphics/GraphicsDevice.h"
#include "graphics/BasicEffect.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/OpenGL.h"
#include "debug/Assert.h"

namespace Graphics
{
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	ModelMeshPart::ModelMeshPart() : displayListInitialized(false)
	{
		Effect = New<BasicEffect>();
		VertexBuffer = New<Graphics::VertexBuffer>();
		IndexBuffer = New<Graphics::IndexBuffer>();
	}

	//-------------------------------------------------------------------------------------------------
	void ModelMeshPart::Draw()
	{
		PROFILE_METHOD(MPDraw);

		ASSERT(VertexBuffer, "Error: No vertex buffer assigned");
		ASSERT(IndexBuffer, "Error: No index buffer assigned");
		ASSERT(Effect->Texture, "No Texture assigned to effect");

		if (!displayListInitialized)
		{
			displayList = DisplayList(*VertexBuffer, *IndexBuffer, *Effect->Texture);
			displayListInitialized = true;
		}

		Effect->Apply();
		glCallList(displayList);
		glPopMatrix(1);
		//GraphicsDevice::Main.VertexBuffer = VertexBuffer;
		//GraphicsDevice::Main.Indices = IndexBuffer;
		//GraphicsDevice::Main.DrawIndexedPrimitives(PrimitiveType::TriangleList, 0, 0, Vertices.size(), 0, IndexBuffer->IndexCount() / 3);
	}
}