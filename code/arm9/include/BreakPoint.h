#pragma once

#include <nds/interrupts.h>
#include "KeyPad.h"

static inline void waitForInput(Input::Keys key)
{
	while(true)
	{
		swiWaitForVBlank();
		Input::KeyPad::ReadState();
		Input::KeyState keys = Input::KeyPad::GetState();
		if (keys.IsKeyPressed(key))
			break;
	}
}

#define BREAKPOINT() waitForInput(Input::Keys::Start)