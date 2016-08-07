#pragma once

#include "core/types.h"
#include "MathFunctions.h"
struct Range
{
	fx12 min, max;

	fx12 Overlap(const Range &other)
	{
		if (min >= other.min && max <= other.max)
			return max - min;
		if (other.min >= min && other.max <= max)
			return other.max - other.min;
		if (min >= other.min && min <= other.max)
			return other.max - min;
		if (max >= other.min && max <= other.max)
			return max - other.min;

		return 0;
	}
};
