#pragma once

#include "types.h"
#include "ModelMeshPart.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"
#include "Profiler.h"

namespace Graphics
{
	class ModelMesh
	{
	public:

		ModelMesh() = default;

		void Draw();

		void AddPart(const ModelMeshPart &part);

		void CreateBoundingBox();

		void CreateBoundingSphere();

	public:

		List<ModelMeshPart> MeshParts;
		Framework::BoundingBox BoundingBox;
		Framework::BoundingSphere BoundingSphere;
	};

	//-------------------------------------------------------------------------------------------------
	inline void ModelMesh::Draw()
	{
		for(u32 i = 0; i < MeshParts.size(); ++i)
			MeshParts[i].Draw();
	}

	//-------------------------------------------------------------------------------------------------
	inline void ModelMesh::AddPart(const ModelMeshPart &part)
	{
		MeshParts.push_back(part);
		CreateBoundingBox();
		CreateBoundingSphere();
	}
}