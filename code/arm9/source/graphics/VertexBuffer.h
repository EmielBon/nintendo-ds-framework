#pragma once

#include "core/types.h"
#include "graphics/EfficientVertex.h"

namespace Graphics
{
	class VertexBuffer
	{
	public:

		VertexBuffer() = default;

		const List<EfficientVertex>& GetData() const;

		void SetData(const List<Vertex> &vertices);

		int VertexCount() const;

		EfficientVertex& operator[](u32 index);

		const EfficientVertex& operator[](u32 index) const;

	private:

		List<EfficientVertex> data;
	};

	//-------------------------------------------------------------------------------------------------
	inline const List<EfficientVertex>& VertexBuffer::GetData() const
	{
		return data;
	}

	//-------------------------------------------------------------------------------------------------
	inline int VertexBuffer::VertexCount() const
	{
		return data.size();
	}

	//-------------------------------------------------------------------------------------------------
	inline EfficientVertex& VertexBuffer::operator[](u32 index)
	{
		return data[index];
	}

	//-------------------------------------------------------------------------------------------------
	inline const EfficientVertex& VertexBuffer::operator[](u32 index) const
	{
		return data[index];
	}
}