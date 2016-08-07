#pragma once

#include "Component.h"
#include "core/types.h"
#include "DrawableGameComponent.h"

namespace GUI
{
	class AbstractButton : public Framework::DrawableGameComponent
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