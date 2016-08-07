#pragma once

#include "core/types.h"
#include "ModelMesh.h"

namespace Graphics
{
	class Model
	{
	public:

		Model() = default;

		/// Render a model after applying the matrix transformations
		void Draw();

		void AddMesh(const ModelMesh &mesh);

	public:

		List<ModelMesh> Meshes;
	};

	//-------------------------------------------------------------------------------------------------
	inline void Model::Draw()
	{
		for(u32 i = 0; i < Meshes.size(); ++i)
			Meshes[i].Draw();
	}

	//-------------------------------------------------------------------------------------------------
	inline void Model::AddMesh(const ModelMesh &mesh)
	{
		Meshes.push_back(mesh);
	}
}