#pragma once

#include "types.h"
#include "fixed.h"

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