#pragma once

#include "core/types.h"
#include "core/fixed.h"

namespace Graphics
{
	/// \todo Rename
	struct EfficientVertex
	{
		u32 XY;
		short Z;
		u32 Normal;
		fx12 U;
		fx12 V;
	};
}