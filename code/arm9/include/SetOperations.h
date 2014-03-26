#pragma once

namespace Util
{
	template <class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_difference (InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		OutputIterator result)
	{
		while (first1!=last1 && first2!=last2)
		{
			if (*first1<*first2) { *result = *first1; ++result; ++first1; }
			else if (*first2<*first1) ++first2;
			else { ++first1; ++first2; }
		}
		return std::copy(first1,last1,result);
	}
}
