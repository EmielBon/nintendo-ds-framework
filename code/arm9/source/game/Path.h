#pragma once

#include "core/types.h"

namespace Framework2D
{
	class Path
	{
	public:

		///
		Path();

		///
		void Add(int x, int y);
		
		///
		Tuple<int, int> operator [](int i);
		
		///
		int Size() const;
		
	public:
			
		List<Tuple<int, int>> Waypoints;
	};

	//-------------------------------------------------------------------------------------------------
	inline Path::Path()
	{
	}
}