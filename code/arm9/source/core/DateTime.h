#pragma once

#include <time.h>
#include "core/types.h"

namespace System
{
	struct DateTime
	{
	public:

		DateTime() = default;

	private:

		int64 ticks;
	};
}