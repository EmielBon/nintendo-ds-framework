#pragma once

#include "types.h"
#include "MathFunctions.h"

namespace Framework
{
	template<class T>
	class Vec2
	{
	public:

		/// 
		Vec2();

		/// 
		Vec2(T x, T y);

		///
		T LengthSquared() const;

		///
		T Length() const;

		///
		Vec2<T> operator*(T s) const;

		///
		Vec2<T> operator+(const Vec2<T> &other) const;

		///
		Vec2<T> operator+=(const Vec2<T> &other);

		///
		Vec2<T> operator-(const Vec2<T> &other) const;

		///
		Vec2<T> operator-=(const Vec2<T> &other);

		/// 
		Vec2<T> Normalize() const;

		/// 
		static Vec2<T> Normalize(const Vec2<T> &v);

		/// 
		static T Dot(const Vec2<T> &left, const Vec2<T> &right);

		///
		//Vec2<T> Transform(const Matrix3x3 &m) const;

		/** \brief Transforms a 3D vector by the given matrix. 
		 *  \param vector The source vector
		 *  \param matrix The transformation matrix
		 *  \returns The transformed vector */
		//static Vec2<T> Transform(const Vec2<T> &vector, const Matrix &matrix);

	public:

		T x, y;
	};

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec2<T>::Vec2() : x(0), y(0)
	{

	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec2<T>::Vec2(T x, T y) : x(x), y(y)
	{
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline T Vec2<T>::Dot(const Vec2<T> &left, const Vec2<T> &right)
	{
		return left.x * right.x + left.y * right.y;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec2<T> Vec2<T>::Normalize() const
	{
		return Normalize(*this);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec2<T> Vec2<T>::Normalize(const Vec2<T> &v)
	{
		T l = v.Length();
		return Vec2<T>(v.x/l, v.y/l);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec2<T> Vec2<T>::operator*(T s) const
	{
		return Vec2<T>(x*s, y*s);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec2<T> Vec2<T>::operator+(const Vec2<T> &other) const
	{
		return Vec2<T>(x + other.x, y + other.y);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec2<T> Vec2<T>::operator+=(const Vec2<T> &other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec2<T> Vec2<T>::operator-(const Vec2<T> &other) const
	{
		return Vec2<T>(x - other.x, y - other.y);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec2<T> Vec2<T>::operator-=(const Vec2<T> &other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline T Vec2<T>::LengthSquared() const
	{
		return x*x + y*y;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline T Vec2<T>::Length() const
	{
		return Math::Sqrt( LengthSquared() );
	}
}

