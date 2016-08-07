#pragma once

#include "core/types.h"

namespace Framework
{
	/// Size type
	struct Size
	{
		int Width;
		int Height;

		Size(u32 width = 0, u32 height = 0) : Width(width), Height(height) 
		{
		}

		bool IsEqual(const Size &other) const
		{
			return (
				Width == other.Width && 
				Height == other.Height
				);
		}

		bool operator==(const Size &other) const
		{
			return this->IsEqual(other);
		}

		bool operator!=(const Size &other) const
		{
			return !(*this == other);
		}
	};
}
