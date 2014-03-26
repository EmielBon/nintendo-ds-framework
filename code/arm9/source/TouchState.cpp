#include "TouchState.h"

#include "KeyPad.h"

namespace Input
{
	//-------------------------------------------------------------------------------------------------
	bool TouchState::IsPressed()
	{
		return KeyPad::GetState().IsKeyPressed(Keys::Touch);
	}

	//-------------------------------------------------------------------------------------------------
	bool TouchState::IsHeld()
	{
		return KeyPad::GetState().IsKeyHeld(Keys::Touch);
	}

	//-------------------------------------------------------------------------------------------------
	bool TouchState::IsReleased()
	{
		return KeyPad::GetState().IsKeyReleased(Keys::Touch);
	}
}