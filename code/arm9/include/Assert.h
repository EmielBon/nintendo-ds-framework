#pragma once

#include <nds/arm9/sassert.h>
#include "StringHelper.h"

#ifdef DEBUG
	#define ASSERT(condition, expr) sassert(condition, expr)
	#define ASSERT2(condition, expr) sassert(condition, ToStr(expr).c_str())
	#define CRASH(message) ASSERT2(false, message)
#else
	#define ASSERT(condition, expr)
	#define ASSERT2(condition, expr)
	#define CRASH(message)
#endif