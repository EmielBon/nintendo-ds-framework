#pragma once

#include "Component.h"
#include "types.h"

namespace GUI
{
	class AbstractButton
	{
	public:

		void AddActionListener(Util::IActionListener* listener);

		void RemoveActionListener(Util::IActionListener* listener);

	protected:

		void FireActionPerformed(void *source);

	private:

		Set<Util::IActionListener*> actionListeners;

	public:

		String Text;
	};
}