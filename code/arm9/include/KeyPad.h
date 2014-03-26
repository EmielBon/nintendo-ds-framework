#pragma once

#include "KeyState.h"

namespace Input
{
	class KeyPad
	{
	public:

		static KeyState GetState();

		static void ReadState();

	private:

		static KeyState currentState;
	};
}