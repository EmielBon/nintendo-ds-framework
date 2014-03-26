#pragma once

#include <nds/arm9/trig_lut.h>

#include "types.h"
#include "Debug.h"
#include "MathFunctions.h"
#include "Logging.h"
#include "FixedHelper.h"
#include "Vec3.h"

namespace Framework
{
	template<class T>
	class Mat
	{
	public:

		Mat();

		Mat(const Mat<T> &other);

		Mat(const std::initializer_list<T> &elements);

		Mat(const Array<T, 16> &elements);

		Mat(Mat<T>&& other);

		~Mat();

		Mat<T>& operator=(const Mat<T> &other);

		Mat<T>& operator=(Mat<T> &&other);

		T& operator[](int index);

		const T& operator[](int index) const;

		Mat<T> operator*(const Mat<T> &other) const;

		static Mat<T> Mul(const Mat<T> &A, const Mat<T> &B);

		static Mat<T> Identity();

		static Mat<T> CreateScale(T scale);

		static Mat<T> CreateScale(const Vector3 &scale);

		static Mat<T> CreateScale(T sx, T sy, T sz);

		static Mat<T> CreateRotationX(T angle);

		static Mat<T> CreateRotationY(T angle);

		static Mat<T> CreateRotationZ(T angle);

		static Mat<T> CreateTranslation(const Vector3 &translation);

		static Mat<T> CreateTranslation(T dx, T dy, T dz);

		static Mat<T> CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector);

		static Mat<T> CreatePerspectiveFieldOfView(float fieldOfView, T aspectRatio, T nearPlaneDistance, T farPlaneDistance);

		static Mat<T> Transpose(const Mat<T> &matrix);

		static Mat<T> CreateTranslationScale(const Vector3 &translation, const Vector3 &scale);

		bool Decompose(Ptr<Vector3> scale, Ptr<Mat<T>> rotation, Ptr<Vector3> translation) const;

		// todo: not in XNA Mat<T> class
		Vector3 ExtractScaling() const;

		// todo: not in XNA Mat<T> class
		Mat<T> ExtractRotation() const;

		// todo: not in XNA Mat<T> class
		Vector3 ExtractTranslation() const;

		// todo: not in XNA Mat<T> class
		Mat<T> RemoveScaling() const;

		// todo: not in XNA Mat<T> class
		Mat<T> RemoveScaling(const Vector3 &scale) const;

	public:

		T *M;
		//Array<T, 16> M;
	};

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T>::Mat()
	{
		M = new T[16];
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T>::Mat(const Mat &other) : Mat()
	{
		std::copy(other.M, other.M + 16, M);
	}

	template<class T>
	inline Mat<T>::Mat(const std::initializer_list<T> &elements) : Mat()
	{
		std::copy(elements.begin(), elements.end(), M);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T>::Mat(const Array<T, 16> &elements) : Mat()
	{
		std::copy(elements.begin(), elements.end(), M);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T>::~Mat()
	{
		delete[] M;
		M = nullptr;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T>& Mat<T>::operator=(const Mat<T> &other)
	{
		if (this != &other)
			std::copy(other.M, other.M + 16, M);
		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T>& Mat<T>::operator=(Mat<T> &&other)
	{
		if (this != &other)
		{
			delete[] M;
			M = other.M;
			other.M = nullptr;
		}
		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline T& Mat<T>::operator[](int index)
	{
		return M[index];
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline const T& Mat<T>::operator[](int index) const
	{
		return M[index];
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::operator*(const Mat<T> &other) const
	{
		return Mul(*this, other);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::Mul(const Mat<T> &A, const Mat<T> &B)
	{
		Mat<T> M;

		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				for (int k = 0; k < 4; ++k)
					M[i + j * 4] = M[i + j * 4] + A[i + k * 4] * B[k + j * 4];

		return M;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::Identity()
	{
		return {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::CreateScale(T scale)
	{
		return Mat<T>::CreateScale(scale, scale, scale);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::CreateScale(T sx, T sy, T sz)
	{
		return {
			sx, 0, 0, 0,
			0, sy, 0, 0,
			0, 0, sz, 0,
			0, 0, 0, 1,
		};
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::CreateScale(const Vector3 &scale)
	{
		return Mat<T>::CreateScale(scale.x, scale.y, scale.z);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::CreateRotationX(T angle)
	{
		T cosa = Math::Cos(angle);
		T sina = Math::Sin(angle);

		return {
			1, 0, 0, 0,
			0, cosa, -sina, 0,
			0, sina, cosa, 0,
			0, 0, 0, 1,
		};
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::CreateRotationY(T angle)
	{
		T cosa = Math::Cos(angle);
		T sina = Math::Sin(angle);

		return {
			cosa, 0, -sina, 0,
			0, 1, 0, 0,
			sina, 0, cosa, 0,
			0, 0, 0, 1,
		};
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::CreateRotationZ(T angle)
	{
		T cosa = Math::Cos(angle);
		T sina = Math::Sin(angle);

		return {
			cosa, -sina, 0, 0,
			sina, cosa, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::CreateTranslation(T dx, T dy, T dz)
	{
		return {
			1, 0, 0, dx,
			0, 1, 0, dy,
			0, 0, 1, dz,
			0, 0, 0, 1,
		};
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::CreateTranslation(const Vector3 &translation)
	{
		return Mat<T>::CreateTranslation(translation.x, translation.y, translation.z);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector)
	{
		Vector3 v = cameraUpVector;
		Vector3 e = cameraPosition; // eye vector
		Vector3 w = Vector3::Normalize(e - cameraTarget); // forward vector
		Vector3 u = Vector3::Normalize(Vector3::Cross(v, w)); // side vector
		// Recompute local up
		v = Vector3::Cross(w, u); // up vector

		return {
			u.x, u.y, u.z, -Vector3::Dot(e, u),
			v.x, v.y, v.z, -Vector3::Dot(e, v),
			w.x, w.y, w.z, -Vector3::Dot(e, w),
			0, 0, 0, 1,
		};
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::CreatePerspectiveFieldOfView(float fieldOfView, T aspectRatio, T nearPlaneDistance, T farPlaneDistance)
	{
		int fovy = fieldOfView * DEGREES_IN_CIRCLE / (2 * Math::Pi);

		T l, r, b, t, n, f;

		t = nearPlaneDistance * Util::FixedHelper::Fromf32<12>(tanLerp(fovy / 2));
		b = -t;
		l = b * aspectRatio;
		r = t * aspectRatio;
		n = nearPlaneDistance;
		f = farPlaneDistance;

		return {
			2 * n / (r - l), 0, (r + l) / (r - l), 0,
			0, 2 * n / (t - b), (t + b) / (t - b), 0,
			0, 0, -(f + n) / (f - n), -2 * f*n / (f - n),
			0, 0, -1, 0,
		};
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::Transpose(const Mat<T> &m)
	{
		Mat<T> result;

		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				result[i + j * 4] = m[j + i * 4];

		ASSERT(result[2 + 3 * 4] == m[3 + 2 * 4], "Error: Wrong matrix transpose result");

		return result;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline bool Mat<T>::Decompose(Ptr<Vector3> scale, Ptr<Mat<T>> rotation, Ptr<Vector3> translation) const
	{
		if (translation != nullptr)
		{
			translation->x = M[3];
			translation->y = M[7];
			translation->z = M[11];
		}

		if (scale != nullptr)
		{
			T xs, ys, zs;

			if (Math::Sign((M[0] * M[1] * M[2] * M[3])) < T(0))
				xs = -1;
			else
				xs = 1;

			if (Math::Sign((M[4] * M[5] * M[6] * M[7])) < T(0))
				ys = -1;
			else
				ys = 1;

			if (Math::Sign((M[8] * M[9] * M[10] * M[11])) < T(0))
				zs = -1;
			else
				zs = 1;

			scale->x = xs * Math::Sqrt(M[0] * M[0] + M[1] * M[1] + M[2] * M[2]);
			scale->y = ys * Math::Sqrt(M[4] * M[4] + M[5] * M[5] + M[6] * M[6]);
			scale->z = zs * Math::Sqrt(M[8] * M[8] + M[9] * M[9] + M[10] * M[10]);
		}

		if (rotation != nullptr)
		{
			if (scale->x == T(0) || scale->y == T(0) || scale->z == T(0))
			{
				*rotation = Mat<T>::Identity();
				return false;
			}

			Array<T, 16> rot = {
				M[0] / scale->x, M[1] / scale->x, M[2] / scale->x, 0,
				M[4] / scale->y, M[5] / scale->y, M[6] / scale->y, 0,
				M[8] / scale->z, M[9] / scale->z, M[10] / scale->z, 0,
				0, 0, 0, 1,
			};

			*rotation = rot;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::RemoveScaling() const
	{
		Ptr<Vector3> scale = New<Vector3>();
		Decompose(scale, nullptr, nullptr);
		return RemoveScaling(*scale);
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::RemoveScaling(const Vector3 &scale) const
	{
		/*if (scale->x == T(0) || scale->y == T(0) || scale->z == T(0))
		{
		LOG_WARNING("Warning: division by 0 in Mat<T>::RemoveScaling()");
		}*/

		return {
			M[0] / scale.x, M[1] / scale.x, M[2] / scale.x, M[3],
			M[4] / scale.y, M[5] / scale.y, M[6] / scale.y, M[7],
			M[8] / scale.z, M[9] / scale.z, M[10] / scale.z, M[11],
			0, 0, 0, 1,
		};
	}

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Mat<T> Mat<T>::CreateTranslationScale(const Vector3 &translation, const Vector3 &scale)
	{
		return{
			scale.x, 0, 0, translation.x,
			0, scale.y, 0, translation.y,
			0, 0, scale.z, translation.z,
			0, 0, 0, 1,
		};
	}
}