#include "TouchScreen.h"
#include <nds/arm9/input.h>

namespace Input
{
	TouchState TouchScreen::currentState;

	//-------------------------------------------------------------------------------------------------
	TouchState TouchScreen::GetState()
	{
		return currentState;
	}

	//-------------------------------------------------------------------------------------------------
	void TouchScreen::ReadState()
	{
		touchRead(&currentState.Position);
	}
}