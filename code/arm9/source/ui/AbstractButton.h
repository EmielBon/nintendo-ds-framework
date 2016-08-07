#pragma once

#include "ui/Component.h"
#include "core/types.h"
#include "game/DrawableGameComponent.h"

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