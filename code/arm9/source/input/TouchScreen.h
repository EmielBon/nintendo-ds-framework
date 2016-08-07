#pragma once

#include "TouchState.h"

namespace Input
{
	class TouchScreen
	{
	public:

		static TouchState GetState();

		static void ReadState();

	private:

		static TouchState currentState;
	};
}
