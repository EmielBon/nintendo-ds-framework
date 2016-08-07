#pragma once

#include "game/IEventListener.h"

namespace Util
{
	class IActionListener : public IEventListener
	{
	public:

		virtual void ActionPerformed(void *source) = 0;
	};
}