#pragma once

#include "Camera.h"
#include "types.h"

namespace Graphics
{
	class FlyingCamera : public Camera
	{
	private:

		using super = Graphics::Camera;

	public:

		///
		FlyingCamera() { };

		///
		virtual ~FlyingCamera() { };

		/// 
		FlyingCamera(Vector3 eye, Vector3 focus, fx12 aspectRatio = 256.0f / 192.0f);

		///
		void Initialize();

		///
		void Update(const GameTime &gameTime);

		/// 
		void UpdateViewMatrix();

		/** \brief Move the camera 
		 *  \param forward Amount of movement in the forward direction
		 *  \param side Amount of horizontal movement 
		 *  \param up Amount of vertical movement */
		void Move(float forward, float side, float up);

		/** \brief Move the camera 
		 *  \param moveVector Relative camera movement as a vector */
		void Move(Vector3 moveVector);

		/** \brief Rotate the camera
		 *  \param yaw Amount of rotation around the camera's up-vector
		 *  \param pitch Amount of rotation around the camera's sideways-vector 
		 *  \param roll Amount of rotation around the camera's forward-vector 
		 *  \todo Roll is unsupported */
		void Rotate(float yaw, float pitch, float roll);

	public:

		fx12 Yaw, Pitch;

	private:

		Vector3 moveVector;
	};

	//-------------------------------------------------------------------------------------------------
	inline void FlyingCamera::Move( float forward, float side, float up )
	{
		Move( Vector3(forward, side, up) );
	}

	//-------------------------------------------------------------------------------------------------
	inline void FlyingCamera::Move( Vector3 move )
	{
		moveVector += move;
	}
}