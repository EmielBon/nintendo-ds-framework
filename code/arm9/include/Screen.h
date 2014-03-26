#pragma once

#include "types.h"
#include "Vec2.h"

namespace Graphics
{
	class Screen
	{
	protected:

		/// Constructor
		Screen() = default;

	public:

		/// Force this Screen to use the Main rendering engine, thus forcing the other screen use the Sub engine
		void UseMainEngine();

		/// Returns whether this Screen is using the Main rendering engine
		//bool HasMainEngine() const;

		///
		static Framework::Point Position8x8ForLocation(int x, int y);

		/// Swap the rendering engines the Screens are using
		static void SwapEngines();

	public:

		static Screen Top;
		static Screen Bottom;
		static const int Width = 256;
		static const int Height = 192;
		static const int Width8x8 = 32;
		static const int Height8x8 = 24;
	};
}
