#include "input/KeyPad.h"
#include <nds/arm9/input.h>

namespace Input
{
	KeyState KeyPad::currentState;

	//-------------------------------------------------------------------------------------------------
	KeyState KeyPad::GetState()
	{
		return currentState;
	}

	//-------------------------------------------------------------------------------------------------
	void KeyPad::ReadState()
	{
		scanKeys();

		currentState.PressedState  = keysDown();
		currentState.HeldState     = keysHeld();
		currentState.ReleasedState = keysUp();
	}
}