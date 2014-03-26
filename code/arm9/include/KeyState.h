#pragma once

#include "Keys.h"

namespace Input
{
	class KeyState
	{
	public:

		/// 
		bool IsKeyPressed(Keys key);

		/// 
		bool IsKeyHeld(Keys key);

		/// 
		bool IsKeyReleased(Keys key);

	public:

		u32 PressedState;
		u32 HeldState;
		u32 ReleasedState;
	};

	//-------------------------------------------------------------------------------------------------
	inline bool KeyState::IsKeyPressed(Keys key)
	{
		return (PressedState & key) != 0; 
	}

	//-------------------------------------------------------------------------------------------------
	inline bool KeyState::IsKeyHeld(Keys key)
	{
		return (HeldState & key) != 0; 
	}

	//-------------------------------------------------------------------------------------------------
	inline bool KeyState::IsKeyReleased(Keys key)
	{
		return (ReleasedState & key) != 0; 
	}
}