#include "FPSCounter.h"
#include "GameTime.h"

namespace Debug
{
	//-------------------------------------------------------------------------------------------------
	FPSCounter::FPSCounter() : frameCount(0), FPS(0)
	{

	}

	//-------------------------------------------------------------------------------------------------
	void FPSCounter::Draw(const Framework::GameTime &gameTime)
	{
		static int elapsedSeconds = 0;

		frameCount++;

		if (gameTime.TotalGameTime.Seconds() > elapsedSeconds)
		{
			elapsedSeconds = gameTime.TotalGameTime.Seconds();
			FPS = frameCount;
			frameCount = 0;
		}
	}
}