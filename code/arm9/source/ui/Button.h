#pragma once

#include "ui/AbstractButton.h"
#include "ui/Component.h"
#include "core/types.h"

namespace GUI
{
	class Button : public AbstractButton, public Component
	{
	private:

		using super = GUI::AbstractButton;

	public:

		Button() = default;

		Button(const String &text, int x, int y, Graphics::Background *background);

		void Tap();

		void Update(const Framework::GameTime &gameTime);

		void Draw(const Framework::GameTime &gameTime);

	public:

		Ptr<Graphics::TextRenderer> tr;
	};
}