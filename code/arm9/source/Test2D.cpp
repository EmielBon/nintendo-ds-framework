#include "Test2D.h"

// Zelda specific stuff
#include "ZeldaStuff.h"

// Stable packages
#include "Framework2D.h"
#include "Backgrounds.h"
#include "Input.h"

// Specific classes
#include "GraphicsDevice.h"
#include "TileSet256.h"

// Debugging
#include "Logging.h"
#include "DebugUI.h"
#include "FPSCounter.h"

#include "SpriteSet.h"
#include "Sprite.h"

namespace Test
{
	using namespace Debug;
	using namespace Input;
	using namespace System;
	using namespace Graphics;
	using namespace Framework;
	using namespace Framework2D;

	//-------------------------------------------------------------------------------------------------
	void Test2D::Initialize()
	{
		Background& bg0 = GraphicsDevice::Main.Background0;
		bg0.Enable();
		bg0.SetLayer(3);

		super::Initialize();
	}

	//-------------------------------------------------------------------------------------------------
	void Test2D::LoadContent()
	{
		auto bg1 = Content.Load<TiledBackground>("newGameMap1");
		auto bg2 = Content.Load<TiledBackground>("newGameMap2");

		//--------------------------ROOM1--------------------------
		Ptr<Room> room1 = CreateRoom("Room1");
		room1->Map = bg1;
		
		Ptr<Link> link = room1->AddGameObject<Link>(50, 50);
		
		/*Ptr<Enemy> enemy = room1->AddGameObject<ShadowLink>(150,150);
		enemy->path = Content.Load<Path>("path");

		Ptr<Enemy> enemy2 = room1->AddGameObject<Chicken>(80,80);
		enemy2->path = Content.Load<Path>("path2");

		Ptr<Enemy> enemy3 = room1->AddGameObject<Guard>(20,80);
		enemy3->path = Content.Load<Path>("path2");*/

		//--------------------------ROOM2--------------------------
		/*Ptr<Room> room2 = CreateRoom("Room2");
		room2->Map = bg2;
		room2->AddGameObject<Link>(100, 100);

		Ptr<Enemy> enemy4 = room2->AddGameObject<ShadowLink>(50,50);
		enemy4->path = Content.Load<Path>("path2");

		Ptr<Enemy> enemy5 = room2->AddGameObject<Cyclops>(20,80);
		enemy5->path = Content.Load<Path>("path2");*/
		
		GoToRoom("Room1");
		
		super::LoadContent();
	}

	//-------------------------------------------------------------------------------------------------
	void Test2D::Update(const GameTime &gameTime)
	{	
		KeyState keys = KeyPad::GetState();
		
		if (keys.IsKeyHeld(Keys::A))
		{
			GoToRoom("Room2");
		}
		else if (keys.IsKeyHeld(Keys::B))
		{
			GoToRoom("Room1");
		}

		super::Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void Test2D::Draw(const GameTime &gameTime)
	{
		super::Draw(gameTime);
	}
}