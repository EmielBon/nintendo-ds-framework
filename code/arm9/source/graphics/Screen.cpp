#include "Screen.h"
#include "GraphicsDevice.h"
#include <nds/arm9/video.h>

namespace Graphics
{
	Screen Screen::Top;
	Screen Screen::Bottom;

	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	/*bool Screen::HasMainEngine() const
	{
		return engine->IsMain();
	}*/

	//-------------------------------------------------------------------------------------------------
	void Screen::UseMainEngine()
	{
		//engine = &Engine::Main;

		if (this == &Top)
		{
			lcdMainOnTop();
		}
		else
		{
			lcdMainOnBottom();
		}
	}
	
	//-------------------------------------------------------------------------------------------------
	void Screen::SwapEngines()
	{
		lcdSwap();
		/*if (Top.HasMainEngine())
			Bottom.UseMainEngine();
		else
			Top.UseMainEngine();*/
	}

	//-------------------------------------------------------------------------------------------------
	Point Screen::Position8x8ForLocation(int x, int y)
	{
		return Point(x / 8, y / 8);
	}
}