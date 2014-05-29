#pragma once

#include "Camera.h"
#include "Mario.h"
#include "types.h"

namespace Framework3D
{
	class GameCamera : public Graphics::Camera
	{
	private:

		using super = Graphics::Camera;

	public:

		GameCamera(Ptr<Test::Mario> mario);

		virtual ~GameCamera() { }

		void Update(const GameTime &gameTime);

	private:

		void CameraFromTarget();

	public:

		Ptr<Test::Mario> target;
	};

	inline GameCamera::GameCamera(Ptr<Test::Mario> mario) : target(mario)
	{
		CameraFromTarget();
		CreateProjectionMatrix(255.0f / 191.0f);
	}
}