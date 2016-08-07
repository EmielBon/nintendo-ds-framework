#pragma once

#include "game/DrawableGameComponent.h"

namespace Debug
{
	class FPSCounter : public Framework::DrawableGameComponent
	{
	public:

		FPSCounter();

	public:

		void Draw(const Framework::GameTime &gameTime);

	private:

		int frameCount;

	public:

		int FPS;
	};
}