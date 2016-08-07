#include "graphics/Palette.h"
#include "graphics/Color.h"

namespace Graphics
{
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	void Palette::AddColor(u16 color)
	{
		Colors.push_back(color);
	}

	//-------------------------------------------------------------------------------------------------
	void Palette::AddColor(float red, float green, float blue)
	{
		AddColor( Color::FromRGB(red, green, blue) );
	}
}