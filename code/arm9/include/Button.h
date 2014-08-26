#pragma once

#include "AbstractButton.h"
#include "Component.h"
#include "types.h"

namespace GUI
{
	class Button : public AbstractButton, public Component
	{
	private:

		using super = GUI::AbstractButton;

	public:

		Button() = default;

		Button(String text, int x, int y, Ptr<Graphics::Background> background);

		void Tap();

		void Update(const Framework::GameTime &gameTime);

		void Draw(const Framework::GameTime &gameTime);

	public:

		Ptr<Graphics::TextRenderer> tr;
	};
}