#pragma once

#include <nds/arm9/sassert.h>
#include "util/StringHelper.h"

#define ASSERT(condition, expr) sassert(condition, expr)
#define ASSERT2(condition, expr) sassert(condition, ToStr(expr).c_str())
#define CRASH(message) ASSERT2(false, message)
