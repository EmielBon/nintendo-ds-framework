#include "debug/DebugUI.h"
#include "graphics/TextRenderer.h"
#include "graphics/VideoRam.h"
#include "graphics/VideoRamBank.h"
#include "util/StringHelper.h"
#include "game/GameTime.h"
#include "graphics/Memory2D.h"
#include "graphics/MemorySlot.h"
#include "debug/Assert.h"
#include "input/TouchScreen.h"
#include "graphics/GraphicsDevice.h"
#include "debug/Console.h"
#include "debug/ProfilingManager.h"
#include "debug/ProfilingResult.h"
#include "graphics/Background.h"
#include <nds/arm9/video.h>

#define TextLayer   GraphicsDevice::Sub.Backgrounds[1]
#define ButtonLayer GraphicsDevice::Sub.Backgrounds[0]

namespace Debug
{
	using namespace GUI;
	using namespace Test;
	using namespace Input;
	using namespace Graphics;
	using namespace Framework;
	using namespace Framework3D;

	Ptr<System::Console> DebugUI::Console;

	//-------------------------------------------------------------------------------------------------
	DebugUI::DebugUI() : mode(DebugMode_PROFILING), redraw(false), modeCount(3)
	{
		
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::Initialize()
	{
		//Console = New<System::Console>(TextLayer);
		//Components.insert(Console.get());
		//ShowConsole();

		previousButton = Button("<", 0, 0, ButtonLayer);
		nextButton = Button(">", 256 - 8 * 1, 0, ButtonLayer);

		previousButton.AddActionListener(this);
		nextButton.AddActionListener(this);

		Components.insert(&previousButton);
		Components.insert(&nextButton);

		tr = New<TextRenderer>(TextLayer);
		Components.insert(tr.get());

		TextLayer->ColorMode = ColorMode16;
		ButtonLayer->ColorMode = ColorMode16;

		base::Initialize();
	}

	void DebugUI::LoadContent()
	{
		base::LoadContent();
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::Update(const GameTime &gameTime)
	{
		//Console->WriteLine("TEST!");
		base::Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::ActionPerformed(void *source)
	{
		if (source == &previousButton)
		{
			mode = ((mode - 1) % modeCount);
			if (mode < 0) mode = (modeCount - 1);
			message = "Left button pressed";
			TextLayer->Offset.y = 0;
			Redraw();
		}
		if (source == &nextButton)
		{
			mode = ((mode + 1) % modeCount);
			message = "Right button pressed";
			TextLayer->Offset.y = 0;
			Redraw();
		}
		tr->DrawText(message, 0, 23, 0);
		Console->WriteLine("hoi");
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::Redraw()
	{
		redraw = true;
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::Draw(const GameTime &gameTime)
	{
		PROFILE_METHOD(DUIDrw);

		static int elapsedSeconds = 0;

		if (!redraw && mode != DebugMode_LOG && (int)gameTime.TotalGameTime.TotalSeconds() <= elapsedSeconds)
			return;
			
		elapsedSeconds = (int)gameTime.TotalGameTime.TotalSeconds();
		
		TextLayer->Clear();
		ButtonLayer->Clear();
		
		switch(mode)
		{
			case DebugMode_VRAM      : DrawVRAMView();      break;
			case DebugMode_LOG       : DrawLogView();       break;
			case DebugMode_PROFILING : DrawProfilingView(); break;
			default                  : ASSERT(false, "Invalid Debugmode"); break;
		}

		redraw = false;

		base::Draw(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::DrawVRAMView()
	{
		TextLayer->Clear();
		PROFILE_METHOD(DUIVRA);
		tr->DrawText(ToStr("FPS: " << fpsCounter.FPS), 1, 3, 0);
		tr->DrawText("VRAM Usage", 1, 5, 0);

		for(int i = 0; i < 9; ++i)
		{
			VideoRamBank& bank = VideoRam::GetBank(i); 
			int bankSize = bank.GetSize() / 1024;
			String user;

			if (bank.IsFree())
			{
				user = "free";
			}
			else
			{
				auto slot = bank.GetOwner();

				Memory2D &memory = slot->GetMemory();
				u32 type = memory.GetType();

				switch(type)
				{
				case Memory_BG:  user = "bg  memory"; break;
				case Memory_SPR: user = "spr memory"; break;
				case Memory_TEX: user = "tex memory"; break;
				default: user = "?"; break;
				}

				user = ToStr((memory.IsMain() ? "main" : "sub ") << " " << user << "[" << slot->GetIndex() << "]");
			}

			tr->DrawText("Bank " + ToStr((char)('A' + i)) + ": " + (bankSize < 100 ? " " : "") + ToStr(bankSize) + " " + user, 1, 7 + i, 0);
		}

		vu16 vertices = GFX_VERTEX_RAM_USAGE;
		vu16 polygons = GFX_POLYGON_RAM_USAGE;
		tr->DrawText(ToStr("verts: " << vertices << " polys: " << polygons), 0, 22, 0);
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::DrawLogView()
	{
		//PROFILE_METHOD(DUILog);
		
		//Console->Update(GameTime());
		//Console->Redraw();
		//Console->Draw(GameTime());
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::DrawProfilingView()
	{
		TextLayer->Clear();
		PROFILE_METHOD(DUIPro);
		auto& results = ProfilingManager::ProfilingResults;

		int counter = 0;

		for(auto it = results.begin(); it != results.end(); ++it)
		{
			tr->DrawText(it->second.ToString(), 1, 3 + counter++, 0);
		}
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::ShowConsole()
	{
		Console->Enabled = true;
		Console->Visible = true;
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::HideConsole()
	{
		Console->Enabled = false;
		Console->Visible = false;
	}
}
