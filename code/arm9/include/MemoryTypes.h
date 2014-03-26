#pragma once

#include "types.h"

namespace Graphics
{
	enum MemoryType
	{
		Memory_NONE = 0,
		Memory_BG   = BIT(0),
		Memory_SPR  = BIT(1),
		Memory_TEX  = BIT(2),
		Memory_PAL  = BIT(3),
		Memory_BGPAL  = Memory_PAL | Memory_BG,
		Memory_SPRPAL = Memory_PAL | Memory_SPR,
		Memory_TEXPAL = Memory_PAL | Memory_TEX,
	};
}