#pragma once

#include "game/DrawableGameComponent.h"
#include "game/IActionListener.h"

#include "core/types.h"
#include "ui/Button.h"
#include "game/FPSCounter.h"

namespace Debug
{
	enum DebugMode
	{
		DebugMode_VRAM = 0,
		DebugMode_LOG  = 1,
		DebugMode_PROFILING = 2,
	};

	class DebugUI : public Framework::DrawableGameComponent, Util::IActionListener
	{
	private:

		using base = Framework::DrawableGameComponent;

	protected:

		///
		DebugUI();
	
	public:

		///
		static DebugUI& Instance();

		/// Inherited methods from DrawableGameComponent
		void Initialize();

		///
		void LoadContent();

		///
		void Update(const Framework::GameTime &gameTime);

		///
		void Draw(const Framework::GameTime &gameTime);

		///
		void Redraw();

		///
		void ActionPerformed(void *source);

		/// Shows the console on sub-engine background 3, on top
		void ShowConsole();

		/// Hides the console
		void HideConsole();

	public:

		/// Draw VRAM view
		void DrawVRAMView();

		///
		void DrawLogView();

		///
		void DrawProfilingView();

	private:

		Ptr<Graphics::TextRenderer> tr;
		int mode;
		bool redraw;

	public:

		GUI::Button previousButton;
		GUI::Button nextButton;
		String message;
		FPSCounter fpsCounter;
		int modeCount;

		static Ptr<System::Console> Console;
	};

	inline DebugUI& DebugUI::Instance()
	{
		static DebugUI debugUI;
		return debugUI;
	}
}
