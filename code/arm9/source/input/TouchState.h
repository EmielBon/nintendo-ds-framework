#pragma once

#include <nds/touch.h>

namespace Input
{
	class TouchState
	{
	public:

		using TouchPosition = touchPosition;

		/// 
		bool IsPressed();

		/// 
		bool IsHeld();

		/// 
		bool IsReleased();

	public:

		TouchPosition Position;
	};

}
