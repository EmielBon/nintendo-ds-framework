#include "Palette.h"
#include "Color.h"

namespace Graphics
{
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	void Palette::AddColor(u16 color)
	{
		Entries.push_back(color);
	}

	//-------------------------------------------------------------------------------------------------
	void Palette::AddColor(float red, float green, float blue)
	{
		AddColor( Color::FromRGB(red, green, blue) );
	}
}