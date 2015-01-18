#pragma once

#include "Keys.h"
#include "types.h"
#include "Vec2.h"

namespace Input
{
	class KeyState
	{
	public:

		/// 
		bool IsKeyPressed(Keys key) const;

		/// 
		bool IsKeyHeld(Keys key) const;

		/// 
		bool IsKeyReleased(Keys key) const;

		///
		Framework::Vector2i GetDirectionalPadVector() const;

	public:

		u32 PressedState;
		u32 HeldState;
		u32 ReleasedState;
	};

	//-------------------------------------------------------------------------------------------------
	inline bool KeyState::IsKeyPressed(Keys key) const
	{
		return (PressedState & (u16)key) != 0;
	}

	//-------------------------------------------------------------------------------------------------
	inline bool KeyState::IsKeyHeld(Keys key) const
	{
		return (HeldState & (u16)key) != 0;
	}

	//-------------------------------------------------------------------------------------------------
	inline bool KeyState::IsKeyReleased(Keys key) const
	{
		return (ReleasedState & (u16)key) != 0; 
	}

	//-------------------------------------------------------------------------------------------------
	inline Framework::Vector2i KeyState::GetDirectionalPadVector() const
	{
		Framework::Vector2i direction;

		if (IsKeyHeld(Keys::Left))
			direction.x = -1;
		else if (IsKeyHeld(Keys::Right))
			direction.x =  1;
		if (IsKeyHeld(Keys::Down))
			direction.y = -1;
		else if (IsKeyHeld(Keys::Up))
			direction.y = 1;

		return direction;
	}
}