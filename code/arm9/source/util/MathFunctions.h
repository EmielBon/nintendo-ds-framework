#pragma once

#include "core/types.h"
#include <math.h>
#include <nds/arm9/math.h>
#include <stdlib.h>
#include <nds/arm9/trig_lut.h>
#include "debug/Assert.h"
#include "StringHelper.h"
#include "FixedHelper.h"

// todo: optimize with nds math hardware
namespace Math
{
	static const float Pi = 3.1415926535897932384626433832795;
	static const float PiOver2 = Pi / 2;
	static const fx12  PiFixed = Pi;
	static const fx12  PiOver2Fixed = PiOver2;

	template<typename T>
	inline T Pow(T x, T y) { return pow(x, y); }

	template<typename T>
	inline T Sqr(T x) { return x * x; }
	
	template<typename T>
	inline T Min(T x, T y) { return (x < y) ? x : y; }
	
	template<typename T>
	inline T Max(T x, T y) { return (x > y) ? x : y; }
	
	template<typename T>
	inline T Abs(T x) { return (x > T(0)) ? x : x * -1; }
	
	template<typename T>
	inline T Sign(T x) { return (x == T(0)) ? T(0) : x / Abs(x); }

	template<typename T>
	inline T Floor(T x) { return (T)((int) x); }

	template<typename T>
	inline T Round(T x) { return ( Sign(x) * Floor(Abs(x) + 0.5f) ); }

	inline float Sqrt(float x) { return sqrt(x); }
	inline fx12  Sqrt(fx12 x)  { return Util::FixedHelper::Fromf32<12>(sqrtf32(Util::FixedHelper::Tof32(x))); }
	
	inline float Sin(float x)  { return sin(x); }
	inline fx12  Sin(fx12 x)   { return Util::FixedHelper::Fromf32<12>(sinLerp((short)degreesToAngle( (float)x * 180 / Pi))); }
	inline float Cos(float x)  { return cos(x); }
	inline fx12  Cos(fx12 x)   { return Util::FixedHelper::Fromf32<12>(cosLerp((short)degreesToAngle( (float)x * 180 / Pi))); }
	inline float Acos(float x) { return acos(x); }
	inline fx12  Acos(fx12 x)   { return Util::FixedHelper::Fromf32<12>(angleToDegrees(acosLerp(Util::FixedHelper::Tof16(x)))); }
	inline float Asin(float x) { return asin(x); }
	inline fx12  Asin(fx12 x)   { return Util::FixedHelper::Fromf32<12>(angleToDegrees(asinLerp(Util::FixedHelper::Tof16(x)))); }
	inline float Random()      { return (float)rand()/(float)RAND_MAX; }
}
