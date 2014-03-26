#pragma once

#include "GameComponent.h"
#include "types.h"
#include "Vec3.h"
#include "Mat.h"

namespace Graphics
{
	class Camera : public GameComponent
	{
	public:

		Camera();

		Camera(Vector3 eye, Vector3 focus, fx12 aspectRatio);

		virtual ~Camera() = default;

		Vector3 LookAt() const;

		Vector3 Side() const;

		virtual void Initialize() { };

		virtual void Update(const GameTime &gameTime);

		void CreateProjectionMatrix(fx12 aspectRatio);

		virtual void UpdateViewMatrix();

		void SetEffectParameters(BasicEffect &effect);

	public:

		Vector3 Eye, Focus, Up;
		Matrix Projection, View;
	};

	//-------------------------------------------------------------------------------------------------
	inline Camera::Camera() : Up(0, 1, 0)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline Camera::Camera(Vector3 eye, Vector3 focus, fx12 aspectRatio) : Eye(eye), Focus(focus), Up(0, 1, 0)
	{
		CreateProjectionMatrix(aspectRatio);
		UpdateViewMatrix();
	}

	inline Vector3 Camera::LookAt() const
	{
		return Vector3::Normalize(Focus - Eye);
	}

	inline Vector3 Camera::Side() const
	{
		return Vector3::Normalize(Vector3::Cross(LookAt(), Up));
	}

	//-------------------------------------------------------------------------------------------------
	inline void Camera::Update(const GameTime &gameTime)
	{
		UpdateViewMatrix();
	}
}