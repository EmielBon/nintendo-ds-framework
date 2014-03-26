#pragma once

#include "DrawableGameComponent.h"
#include "IActionListener.h"

#include "types.h"
#include "Button.h"

namespace Test
{
	class Test3D;
}

namespace Debug
{
	enum DebugMode
	{
		DebugMode_VRAM = 0,
		DebugMode_LOG  = 1,
		DebugMode_SETTINGS = 2,
		DebugMode_PROFILING = 3,
	};

	class DebugUI : public Framework::DrawableGameComponent, Util::IActionListener
	{
	public:

		///
		DebugUI(Test::Test3D* game);

		/// Inherited methods from DrawableGameComponent
		void Initialize();

		///
		void Update(const Framework::GameTime &gameTime);

		///
		void Draw(const Framework::GameTime &gameTime);

		///
		void Redraw();

		///
		void ActionPerformed(void *source);

		///
		void InitializeConsole();

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
		void DrawSettingsView();

		///
		void DrawProfilingView();

	private:

		Ptr<Graphics::TextRenderer> tr;
		int mode;
		bool redraw;

	public:

		int FPS;
		GUI::Button button1;
		GUI::Button button2;
		String message;

		GUI::Button bboxButton;
		GUI::Button cameraButton;
		GUI::Button collisionButton;

		static Ptr<System::Console> Console;
		Test::Test3D* game;
	};
}