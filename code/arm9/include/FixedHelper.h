#pragma once

#include "fixed.h"

namespace Util
{
	class FixedHelper
	{
	public:

		template<int f>
		static fixed<f> Fromf32(int f32)
		{
			return fixed<f>::Fromf32(f32);
		}

		template<int f>
		static int Tof32(fixed<f> x)
		{
			return x.number;
		}

		template<int f>
		static short Tof16(fixed<f> x)
		{
			return x.number;
		}
	};
}