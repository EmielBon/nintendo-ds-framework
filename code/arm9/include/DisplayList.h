#pragma once

#include "types.h"

namespace Graphics
{
	class DisplayList
	{
	public:

		DisplayList() { };

		DisplayList(const VertexBuffer &vertexBuffer, const IndexBuffer &indexBuffer, const Texture &texture);

		operator u32*();

	private:

		List<u32> displayList;
	};

	//-------------------------------------------------------------------------------------------------
	inline DisplayList::operator u32*()
	{
		return displayList.data();
	}
}