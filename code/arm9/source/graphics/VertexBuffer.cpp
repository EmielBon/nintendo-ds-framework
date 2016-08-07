#include "VertexBuffer.h"

#include "Vertex.h"
#include "FixedHelper.h"
#include <nds/arm9/videoGL.h>

namespace Graphics
{
	using namespace Util;

	//-------------------------------------------------------------------------------------------------
	void VertexBuffer::SetData(const List<Vertex> &vertices)
	{
		for(u32 i = 0; i < vertices.size(); ++i)
		{
			EfficientVertex vertex;
			const Vertex &v = vertices[i];
			v16 x = FixedHelper::Tof16(v.Position.x);
			v16 y = FixedHelper::Tof16(v.Position.y);
			vertex.XY = VERTEX_PACK(x, y);
			vertex.Z = FixedHelper::Tof16(v.Position.z);
			// todo: inefficient, conversion from fx12 to float, then to fx10
			v10 nx = floattov10((float)v.Normal.x);
			v10 ny = floattov10((float)v.Normal.y);
			v10 nz = floattov10((float)v.Normal.z);
			vertex.Normal = NORMAL_PACK(nx, ny, nz);
			vertex.U = v.TextureCoordinates.x;
			vertex.V = v.TextureCoordinates.y;
			data.push_back(vertex);
		}
	}
}