#include "GameCamera.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	void GameCamera::Update(const GameTime &gameTime)
	{
		CameraFromTarget();
		super::Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void GameCamera::CameraFromTarget()
	{
		Vector3 pos = target->position;
		Eye = Vector3(pos.x, 1.0f, pos.y + 4);
		Focus = Vector3(pos.x, 0.5f, pos.y);
	}
}