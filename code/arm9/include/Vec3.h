#pragma once

#include "types.h"
#include "MathFunctions.h"

namespace Framework
{
	template<class T>
	class Vec3
	{
	public:

		/// 
		Vec3();

		/// 
		Vec3(T x, T y, T z);

		///
		Vec3(const std::initializer_list<T> &elements);

		///
		T LengthSquared() const;

		///
		T Length() const;

		///
		Vec3<T> operator*(T s) const;

		///
		Vec3<T> operator*(const Vec3<T> &other) const;

		///
		Vec3<T> operator*=(const Vec3<T> &other);

		///
		Vec3<T> operator+(const Vec3<T> &other) const;

		///
		Vec3<T> operator+=(const Vec3<T> &other);

		///
		Vec3<T> operator-(const Vec3<T> &other) const;

		///
		Vec3<T> operator-=(const Vec3<T> &other);

		/// 
		template<class S>
		explicit operator Vec3<S>() const
		{
			return Vec3<S>((S)x, (S)y, (S)z);
		}

		/// 
		Vec3<T> Normalize() const;

		/// 
		static Vec3<T> Normalize(const Vec3<T> &v);

		/// 
		static T Dot(const Vec3<T> &left, const Vec3<T> &right);

		///
		static Vec3<T> Cross(const Vec3<T> &left, const Vec3<T> &right);
		
		///
		Vec3<T> Transform(const Array<T, 16> &matrix) const;

		///
		Vec3<T> Transform(const T *matrix) const;

		/** \brief Transforms a 3D vector by the given matrix. 
		 *  \param vector The source vector
		 *  \param matrix The transformation matrix
		 *  \returns The transformed vector */
		static Vec3<T> Transform(const Vec3<T> &vector, const Array<T, 16> &matrix);
		
		///
		static Vec3<T> Transform(const Vec3<T> &vector, const T *matrix);

		///
		static Vec3<T> Sign(const Vec3<T> &vector);

		/// 
		String ToString() const;

		static Vec3<T> Zero()
		{
			return Vec3<T>(0, 0, 0);
		}

		static Vec3<T> UnitX()
		{
			return Vec3<T>(1, 0, 0);
		}

		static Vec3<T> UnitY()
		{
			return Vec3<T>(0, 1, 0);
		}

		static Vec3<T> UnitZ()
		{
			return Vec3<T>(0, 0, 1);
		}

	public:

		T x, y, z;
	};

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec3<T>::Vec3() : x(0), y(0), z(0)
	{

	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec3<T>::Vec3(T x, T y, T z) : x(x), y(y), z(z)
	{
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline T Vec3<T>::Dot(const Vec3<T> &left, const Vec3<T> &right)
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec3<T> Vec3<T>::Normalize() const
	{
		return Normalize(*this);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec3<T> Vec3<T>::Normalize(const Vec3<T> &v)
	{
		T l = v.Length();
		return Vec3<T>(v.x / l, v.y / l, v.z / l);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec3<T> Vec3<T>::operator*(T s) const
	{
		return Vec3<T>(x*s, y*s, z*s);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec3<T> Vec3<T>::operator*(const Vec3<T> &other) const
	{
		return Vec3<T>(x * other.x, y * other.y, z * other.z);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec3<T> Vec3<T>::operator*=(const Vec3<T> &other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec3<T> Vec3<T>::operator+(const Vec3<T> &other) const
	{
		return Vec3<T>(x + other.x, y + other.y, z + other.z);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec3<T> Vec3<T>::operator+=(const Vec3<T> &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec3<T> Vec3<T>::operator-(const Vec3<T> &other) const
	{
		return Vec3<T>(x - other.x, y - other.y, z - other.z);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec3<T> Vec3<T>::operator-=(const Vec3<T> &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline T Vec3<T>::LengthSquared() const
	{
		return x*x + y*y + z*z;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline T Vec3<T>::Length() const
	{
		return Math::Sqrt( LengthSquared() );
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec3<T> Vec3<T>::Transform(const Vec3<T> &vector, const T *matrix)
	{
		return vector.Transform(matrix);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Vec3<T> Vec3<T>::Transform(const Vec3<T> &vector, const Array<T, 16> &matrix)
	{
		return vector.Transform(matrix);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	Vec3<T> Vec3<T>::Transform(const Array<T, 16> &matrix) const
	{
		return Transform(matrix.data());
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	Vec3<T> Vec3<T>::Transform(const T *m) const
	{
		Vec3<T> v;
		
		v.x = m[ 0] * x + m[ 1] * y + m[ 2] * z + m[ 3];
		v.y = m[ 4] * x + m[ 5] * y + m[ 6] * z + m[ 7];
		v.z = m[ 8] * x + m[ 9] * y + m[10] * z + m[11];
		T w = m[12] * x + m[13] * y + m[14] * z + m[15];

		// Homogenize
		v.x = v.x / w;
		v.y = v.y / w;
		v.z = v.z / w;

		return v;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	Vec3<T> Vec3<T>::Cross(const Vec3<T> &left, const Vec3<T> &right)
	{
		Vec3<T> result;
		result.x = left.y * right.z - left.z * right.y;
		result.y = left.z * right.x - left.x * right.z;
		result.z = left.x * right.y - left.y * right.x;
		return result;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	String Vec3<T>::ToString() const
	{
		return ToStr((float)x << " " << (float)y << " " << (float)z);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	Vec3<T> Vec3<T>::Sign(const Vec3<T> &vector)
	{
		return Vec3<T>(Math::Sign(vector.x), Math::Sign(vector.y), Math::Sign(vector.z));
	}
}

