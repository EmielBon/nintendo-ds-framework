#include "Path.h"

namespace Framework2D
{
	//-------------------------------------------------------------------------------------------------
	void Path::Add(int x, int y)
	{
		Waypoints.push_back( std::make_tuple( x, y ) );
	}

	//-------------------------------------------------------------------------------------------------
	Tuple<int, int> Path::operator [](int i)
	{
		return Waypoints[i];
	}

	//-------------------------------------------------------------------------------------------------
	int Path::Size() const
	{
		return Waypoints.size();
	}
}