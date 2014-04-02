#pragma once

#include <nds/arm9/sassert.h>

namespace Util
{
	class FixedHelper;
}

/// Fixed point real number
template<int f>
struct fixed
{
	friend class Util::FixedHelper;

public:

	fixed<f>() : number(0)
	{

	}

	fixed<f>(int x)
	{
		sassert(x < MAX_VALUE, "Fixed point overflow");
		number = x << f;
	}

	fixed<f>(int64 x)
	{
		sassert(x < MAX_VALUE, "Fixed point overflow");
		number = x << f;
	}

	fixed<f>(float x)
	{
		sassert(x < MAX_VALUE, "Fixed point overflow");
		number = (int)(x * (1 << f) + (x >= 0 ? 0.5f : -0.5f));
	}

	template<int g>
	fixed<f>(fixed<g> x)
	{	
	if (f > g)
		number = x.number << (f - g);
	else
		number = x.number >> (g - f);
	}

	fixed<f> operator+(const fixed<f> &other) const
	{
		return Fromf32(number + other.number);
	}

	fixed<f> operator+=(const fixed<f> &other)
	{
		return Fromf32(number += other.number);
	}

	fixed<f> operator-() const
	{
		return Fromf32(-number);
	}

	fixed<f> operator-(const fixed<f> &other) const
	{
		return Fromf32(number - other.number);
	}

	fixed<f> operator-=(const fixed<f> &other)
	{
		return Fromf32(number -= other.number);
	}

	fixed<f> operator*(const fixed<f> &other) const
	{
		sassert((number >> 12) * (other.number >> 12) < MAX_VALUE, "Fixed Point Overflow");

		int64 result = (int64)number * other.number;
		return Fromf32((int)(result >> f));
	}

	fixed<f> operator*=(const fixed<f> &other)
	{
		fixed<f> x = *this * other;
		number = x.number;
		return *this;
	}

	fixed<f> operator/(const fixed<f> &other) const
	{
		int result = (int)(((int64)number << f) / (int64)other.number);
		return Fromf32(result);
	}

	fixed<f> operator/=(const fixed<f> &other)
	{
		fixed<f> x = *this / other;
		number = x.number;
		return *this;
	}

	bool operator==(const fixed<f> &other) const
	{
		return number == other.number;
	}

	bool operator!=(const fixed<f> &other) const
	{
		return !(*this == other);
	}

	bool operator<(const fixed<f> &other) const
	{
		return number < other.number;
	}

	bool operator<=(const fixed<f> &other) const
	{
		return number <= other.number;
	}

	bool operator>(const fixed<f> &other) const
	{
		return number > other.number;
	}

	bool operator>=(const fixed<f> &other) const
	{
		return number >= other.number;
	}

	explicit operator int() const
	{
		return (number >> f);
	}

	explicit operator int64() const
	{
		return (number >> f);
	}

	explicit operator short() const
	{
		return (number >> f);
	}

	explicit operator float() const
	{
		return (float)number / (1 << f);
	}

private:

	static fixed<f> Fromf32(int f32)
	{
		fixed<f> x;
		x.number = f32;
		return x;
	}

public:

	static const int MAX_VALUE = 1 << (31 - f);

public:

	int number;
};

template<typename T, int f>
inline fixed<f> operator+(fixed<f> f32, T x)
{
	return f32 + fixed<f>(x);
}

template<typename T, int f>
inline fixed<f> operator+(T x, fixed<f> f32)
{
	return fixed<f>(x) + f32;
}

template<typename T, int f>
inline fixed<f> operator-(fixed<f> f32, T x)
{
	return f32 - fixed<f>(x);
}

template<typename T, int f>
inline fixed<f> operator-(T x, fixed<f> f32)
{
	return fixed<f>(x) - f32;
}

template<typename T, int f>
inline fixed<f> operator*(fixed<f> f32, T x)
{
	return f32 * fixed<f>(x);
}

template<typename T, int f>
inline fixed<f> operator*(T x, fixed<f> f32)
{
	return fixed<f>(x) * f32;
}

template<typename T, int f>
inline fixed<f> operator/(fixed<f> f32, T x)
{
	return f32 / fixed<f>(x);
}

template<typename T, int f>
inline fixed<f> operator/(T x, fixed<f> f32)
{
	return fixed<f>(x) / f32;
}