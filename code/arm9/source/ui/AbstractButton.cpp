#include "ui/AbstractButton.h"
#include "game/IActionListener.h"

namespace GUI
{
	using namespace Util;

	//-------------------------------------------------------------------------------------------------
	void AbstractButton::AddActionListener(IActionListener* listener)
	{
		actionListeners.insert(listener);
	}

	//-------------------------------------------------------------------------------------------------
	void AbstractButton::RemoveActionListener(IActionListener* listener)
	{
		actionListeners.erase(listener);
	}

	//-------------------------------------------------------------------------------------------------
	void AbstractButton::FireActionPerformed(void *source)
	{
		for(auto it = actionListeners.begin(); it != actionListeners.end(); ++it)
		{
			(*it)->ActionPerformed(source);
		}
	}
}
