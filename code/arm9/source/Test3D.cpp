#include "Test3D.h"

// Stable libraries
#include "Framework.h"
#include "Input.h"

// Specific libraries
#include "VideoRam.h"

// 2D graphics
#include "TileSet256.h"
#include "Palette.h"
#include "Background.h"
#include "TilesManager.h"
#include "Map.h"

// 3D Graphics
#include "GraphicsDevice.h"
#include "GameCamera.h"
#include "FlyingCamera.h"
#include "Mat.h"
#include "Model.h"
#include "Vec3.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Scene.h"
#include "Light.h"

// Game classes
#include "Mario.h"

// Debug
#include "Debug.h"

namespace Test
{
	using namespace Util;
	using namespace Debug;
	using namespace Input;
	using namespace System;
	using namespace Framework3D;

	//-------------------------------------------------------------------------------------------------
	Test3D::Test3D()
	{
		graphics = GraphicsDeviceManager(this);
	}

	//-------------------------------------------------------------------------------------------------
	void Test3D::Initialize()
	{
		fpsCounter = New<FPSCounter>();
		Components.Add(fpsCounter);

		GraphicsDevice::Main.TextureMemory.AutomaticExpansion = false;
		GraphicsDevice::Main.TextureMemory.AssignBankToSlot(BankA, 0);
		GraphicsDevice::Main.TextureMemory.AssignBankToSlot(BankB, 1);
		GraphicsDevice::Main.TextureMemory.AssignBankToSlot(BankC, 2);
		GraphicsDevice::Main.TextureMemory.AssignBankToSlot(BankD, 3);

		debugUI = New<DebugUI>(this);
		Components.Add(debugUI);
		
		// Enable 3D on the main engine
		GraphicsDevice::Main.Enable3D(true);
		// Enable background 0 (used for 3D rendering)
		Background& bg0 = GraphicsDevice::Main.Background0;
		bg0.Enable();
		bg0.SetLayer(0);
		// Enable background 1 (background)
		Background& bg1 = GraphicsDevice::Main.Background1;
		bg1.Enable();
		bg1.SetLayer(1);
		// Set up the graphics device
		GraphicsDevice.RasterizerState.CullMode = CullMode::None;
		graphics.PreferMultiSampling = false;
		graphics.ApplyChanges();
		// Set the color for the background
		GraphicsDevice::Main.SetBackgroundColor( Color::DeepSkyBlue );

		super::Initialize();
	}

	//-------------------------------------------------------------------------------------------------
	void Test3D::LoadContent()
	{
		scene = Content.Load<Scene>("scene");
		scene->Lights.push_back(Light(Color::White, Vector3(0, -1, -1)));
		scene->Ambient = Color::Gray;
		Components.Add(scene);
		// Init mario
		Ptr<Mario> mario = New<Mario>();
		mario->scene = scene;
		mario->position.y = 4;
		mario->position.z = 0.01f;
		mario->Solid = true;
		scene->AddObject(mario);
		
		/*Ptr<Enemy3D> enemy = New<Enemy3D>("shell");
		enemy->scene = scene;
		enemy->position.x = 3;
		enemy->position.y = 4;
		enemy->position.z = 0.01f;
		enemy->Solid = true;
	
		scene->AddObject(enemy);*/
		
		scene->Camera = New<GameCamera>(mario);
		
		// Create the background
		auto tileSet = Content.Load<TileSet256>("background");
		tileSet->SetPalette( Content.Load<Palette>("background_pal") );
		tileSet->Transparent = false;
		
		auto &map = GraphicsDevice.BackgroundMemory.Maps[0];
		
		for(int i = 0; i < tileSet->GetTileCount8x8(); ++i)
		{
			map.SetTile(i, TilesManager::IdentifierForTile(tileSet, i) );
		}

		super::LoadContent();
	}

	//-------------------------------------------------------------------------------------------------
	void Test3D::Update(const GameTime &gameTime)
	{	
		PROFILE_METHOD(T3DUpd);

		super::Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void Test3D::Draw(const GameTime &gameTime)
	{
		PROFILE_METHOD(T3DDrw);

		// Clear the render target in a predetermined color
		GraphicsDevice.Clear(ClearOptions::Target, Color::DeepSkyBlue);
		
		GraphicsDevice::Main.Background1.ColorMode = ColorMode::ColorMode256;
		GraphicsDevice::Main.Background1.ShowMap(0);

		debugUI->FPS = fpsCounter->FPS;

		super::Draw(gameTime);
	}
}