#include "Component.h"

namespace GUI
{
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	bool Component::Contains(int x, int y)
	{
		Point& position = Bounds.Position;
		Size&  size     = Bounds.Size;

		return (x >= position.x && x <= position.x + size.Width &&
			    y >= position.y && y <= position.y + size.Height);
	}
}