#pragma once

#include "types.h"
#include <nds/input.h>

namespace Input
{
	enum Keys : u16
	{
		A = KEY_A, // Keypad A button
		B = KEY_B, // Keypad B button
		X = KEY_X, // Keypad X button
		Y = KEY_Y, // Keypad Y button
		L = KEY_L, // Left shoulder button
		R = KEY_R, // Right shoulder button
		Up    = KEY_UP,    // Keypad UP button
		Down  = KEY_DOWN,  // Keypad DOWN button
		Left  = KEY_LEFT,  // Keypad LEFT button
		Right = KEY_RIGHT, // Keypad RIGHT button
		Start  = KEY_START,  // Keypad START button
		Select = KEY_SELECT, // Keypad SELECT button
		All = A | B | X | Y | L | R | Up | Down | Left | Right | Start | Select,
		Touch = KEY_TOUCH,
	};
}