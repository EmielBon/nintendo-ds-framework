#pragma once

#include <nds/ndstypes.h>
#include <array>
#include <string>
#include <cstring>
#include <vector>
#include <memory>
#include <set>
#include <list>
#include <map>
#include <utility>
#include <tuple>
#include <stack>
#include <sstream>
#include <initializer_list>
#include "fixed.h"

// Template aliases
template<class T> using Ptr = std::shared_ptr<T>;
template<class T> using WeakPtr = std::weak_ptr<T>;
template<class T> using UniquePtr = std::unique_ptr<T>;
template<class T> using List = std::vector<T>;
template<class T> using Set = std::set<T>;
template<class T> using LinkedList = std::list<T>;
template<class T> using Stack = std::stack<T>;
template<class... T> using Tuple = std::tuple<T...>;
template<class T, int N> using Array = std::array<T, N>;
template<class T, class U> using Dictionary = std::map<T, U>;

/// Aliases
using String = std::string;
using StringBuilder = std::stringstream;
using fx4 = fixed<4>;
using fx8 = fixed<8>;
using fx12 = fixed<12>;
using fx16 = fixed<16>;
using fx24 = fixed<24>;

// Defines
#define New        std::make_shared
#define NewUnique  std::make_unique
#define MakePair   std::make_pair
#define MakeTuple  std::make_tuple

#define finline __attribute__((always_inline)) inline

template<typename T, typename U>
inline static bool IsOfType(Ptr<U> x)
{
	return (bool)std::dynamic_pointer_cast<T>(x);
}

#ifndef NULL
	#define NULL 0
#endif