#include "DebugUI.h"
#include "TextRenderer.h"
#include "VideoRam.h"
#include "VideoRamBank.h"
#include "StringHelper.h"
#include "GameTime.h"
#include "Memory2D.h"
#include "MemorySlot.h"
#include "Assert.h"
#include "TouchScreen.h"
#include "GraphicsDevice.h"
#include "Console.h"
#include "Scene.h"
#include "Test3D.h"
#include "FlyingCamera.h"
#include "GameCamera.h"
#include "ProfilingManager.h"
#include "ProfilingResult.h"

#include <nds/arm9/video.h>

#define TextLayer   GraphicsDevice::Sub.Background1
#define ButtonLayer GraphicsDevice::Sub.Background0

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
	DebugUI::DebugUI(Test3D* game) : mode(DebugMode_PROFILING), redraw(false), FPS(0), game(game)
	{
		// Top layer
		ButtonLayer.Enable();
		ButtonLayer.SetLayer(0);
		ButtonLayer.ShowMap(0);

		// Bottom layer
		TextLayer.Enable();
		TextLayer.SetLayer(1);
		TextLayer.ShowMap(1);

		InitializeConsole();

		button1         = Button("Links",             0,           0, ButtonLayer);
		button2         = Button("Rechts",  256 - 8 * 6,           0, ButtonLayer);
		bboxButton      = Button("Enable BBOXs",      0, 40 + 16 * 0, ButtonLayer);
		cameraButton    = Button("Switch Camera",     0, 40 + 16 * 1, ButtonLayer);
		collisionButton = Button("Toggle Collisions", 0, 40 + 16 * 2, ButtonLayer);

		button1.AddActionListener(this);
		button2.AddActionListener(this);
		bboxButton.AddActionListener(this);
		cameraButton.AddActionListener(this);
		collisionButton.AddActionListener(this);
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::Initialize()
	{
		LOG_DISABLE();
		tr = New<TextRenderer>( TextLayer );
		tr->LoadContent();
		LOG_ENABLE();
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::Update(const GameTime &gameTime)
	{
		button1.Update(gameTime);
		button2.Update(gameTime);

		if (mode == DebugMode_SETTINGS)
		{
			bboxButton.Update(gameTime);
			cameraButton.Update(gameTime);
			collisionButton.Update(gameTime);
		}
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::ActionPerformed(void *source)
	{
		if (source == &button1)
		{
			mode = ((mode - 1) % 4);
			if (mode < 0) mode = 3;
			message = "Left button pressed";
			Redraw();
		}
		if (source == &button2)
		{
			mode = ((mode + 1) % 4);
			message = "Right button pressed";
			Redraw();
		}
		if (source == &bboxButton)
		{
			game->scene->BoundingBoxesVisible = !game->scene->BoundingBoxesVisible;
		}
		if (source == &cameraButton)
		{
			Ptr<Camera> &camera = game->scene->Camera;
			auto mario = std::dynamic_pointer_cast<Mario>( game->scene->GetObject("mario") );
			
			if (IsOfType<FlyingCamera>(camera))
			{
				camera = New<GameCamera>(mario);
				mario->Enabled = true;
			}
			else
			{
				camera = New<FlyingCamera>(camera->Eye, camera->Focus);
				mario->Enabled = false;
			}
		}
		if (source == &collisionButton)
		{
			auto mario = std::dynamic_pointer_cast<Mario  >( game->scene->GetObject("mario") );
			
			mario->CollisionsEnabled = !mario->CollisionsEnabled;
		}
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
		
		ButtonLayer.Clear();
		TextLayer.Clear();
		
		switch(mode)
		{
			case DebugMode_VRAM      : DrawVRAMView();      break;
			case DebugMode_LOG       : DrawLogView();       break;
			case DebugMode_SETTINGS  : DrawSettingsView();  break;
			case DebugMode_PROFILING : DrawProfilingView(); break;
			default                  : ASSERT(false, "Invalid Debugmode"); break;
		}

		button1.Draw(gameTime);
		button2.Draw(gameTime);

		redraw = false;
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::DrawVRAMView()
	{
		PROFILE_METHOD(DUIVRA);
		tr->DrawText(ToStr("FPS: " << FPS), 1, 3, 0);
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

		tr->DrawText(message, 0, 23, 0);
		tr->Draw(GameTime());
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::DrawLogView()
	{
		PROFILE_METHOD(DUILog);
		Console->Update(GameTime());
		Console->Draw(GameTime());
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::DrawSettingsView()
	{
		PROFILE_METHOD(DUISet);
		bboxButton.Draw(GameTime());
		cameraButton.Draw(GameTime());
		collisionButton.Draw(GameTime());
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::DrawProfilingView()
	{
		PROFILE_METHOD(DUIPro);
		auto& results = ProfilingManager::ProfilingResults;

		int counter = 0;

		for(auto it = results.begin(); it != results.end(); ++it)
		{
			tr->DrawText(it->second.ToString(), 1, 3 + counter++, 0);
		}
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::InitializeConsole()
	{
		static bool initialized = false;

		if (!initialized)
		{
			Console = New<System::Console>(TextLayer, 16, 16, 256 - 32, 192 - 32);
			//Components.Add(Console);
			LOG_DISABLE();
			Console->LoadContent();
			LOG_ENABLE();
			ShowConsole();
			for(u32 i = 0; i < StandardLog.Colors.size(); ++i)
			{
				LogPrinter::Print(StandardLog.Colors[i], 0);
 			}
			initialized = true;
		}
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::ShowConsole()
	{
		Background& bg = Console->Background;
		bg.Enable();
		bg.SetLayer(0);

		Console->Enabled = true;
		Console->Visible = true;
	}

	//-------------------------------------------------------------------------------------------------
	void DebugUI::HideConsole()
	{
		Console->Enabled = false;
		Console->Visible = false;
		Console->Background.Disable();
	}
}