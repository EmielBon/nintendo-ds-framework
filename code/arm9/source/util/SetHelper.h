#pragma once

#include "core/types.h"
#include <algorithm>
#include <iterator>

namespace Util
{
	class SetHelper
	{
	public:

		template<class T>
		static Set<T> Difference(const Set<T> &x, const Set<T> &y);
	};

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Set<T> SetHelper::Difference(const Set<T> &x, const Set<T> &y)
	{
		Set<T> result;
		set_difference(x.begin(), x.end(), y.begin(), y.end(), std::inserter(result, result.end()));
		return result;
	}
}
