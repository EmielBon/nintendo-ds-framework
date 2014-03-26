#include "ModelMesh.h"
#include "types.h"
#include "Vec3.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	void ModelMesh::CreateBoundingBox()
	{
		Vector3 pMin, pMax;
		
		for(auto meshpart = MeshParts.begin(); meshpart != MeshParts.end(); ++meshpart)
		{
			List<Vertex> &vertices = meshpart->Vertices;

			for(u32 i = 0; i < vertices.size(); ++i)
			{
				Vertex &vertex = vertices[i];

				if(vertex.Position.x < pMin.x) pMin.x = vertex.Position.x;
				if(vertex.Position.y < pMin.y) pMin.y = vertex.Position.y;
				if(vertex.Position.z < pMin.z) pMin.z = vertex.Position.z;
				if(vertex.Position.x > pMax.x) pMax.x = vertex.Position.x;
				if(vertex.Position.y > pMax.y) pMax.y = vertex.Position.y;
				if(vertex.Position.z > pMax.z) pMax.z = vertex.Position.z;
			}
		}
		

		BoundingBox = Framework::BoundingBox(pMin, pMax);
	}

	//-------------------------------------------------------------------------------------------------
	void ModelMesh::CreateBoundingSphere()
	{
		Vector3 pMin, pMax;
		
		for(auto meshpart = MeshParts.begin(); meshpart != MeshParts.end(); ++meshpart)
		{
			List<Vertex> &vertices = meshpart->Vertices;

			for(u32 i = 0; i < vertices.size(); ++i)
			{
				Vertex &vertex = vertices[i];

				if(vertex.Position.x < pMin.x) pMin.x = vertex.Position.x;
				if(vertex.Position.y < pMin.y) pMin.y = vertex.Position.y;
				if(vertex.Position.z < pMin.z) pMin.z = vertex.Position.z;
				if(vertex.Position.x > pMax.x) pMax.x = vertex.Position.x;
				if(vertex.Position.y > pMax.y) pMax.y = vertex.Position.y;
				if(vertex.Position.z > pMax.z) pMax.z = vertex.Position.z;
			}
		}

		BoundingSphere = Framework::BoundingSphere::CreateFromBoundingBox(Framework::BoundingBox(pMin, pMax));
	}
}