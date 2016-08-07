#include "apps/Test3D.h"

// Stable libraries
#include "game/Framework.h"
#include "input/Input.h"

// Specific libraries
#include "graphics/VideoRam.h"

// 2D graphics
#include "graphics/TileSet256.h"
#include "graphics/Palette.h"
#include "graphics/Background.h"
#include "graphics/Map.h"
#include "graphics/BackgroundMemory.h"

// 3D Graphics
#include "graphics/GraphicsDevice.h"
#include "game/GameCamera.h"
#include "game/FlyingCamera.h"
#include "util/Mat.h"
#include "graphics/Model.h"
#include "graphics/TextureMemory.h"
#include "util/Vec3.h"
#include "graphics/Vertex.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"

#include "game/Scene.h"
#include "graphics/Light.h"

// Game classes
#include "apps/Mario.h"

// Debug
#include "debug/Debug.h"

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
		GraphicsDevice::Main.TextureMemory->AutomaticExpansion = false;
		GraphicsDevice::Main.TextureMemory->AssignBankToSlot(BankA, 0);
		GraphicsDevice::Main.TextureMemory->AssignBankToSlot(BankB, 1);
		GraphicsDevice::Main.TextureMemory->AssignBankToSlot(BankC, 2);
		GraphicsDevice::Main.TextureMemory->AssignBankToSlot(BankD, 3);
		
		// Enable 3D on the main engine
		GraphicsDevice::Main.Enable3D(true);
		// Set up the graphics device
		GraphicsDevice.RasterizerState.CullMode = CullMode::None;
		graphics.PreferMultiSampling = false;
		graphics.ApplyChanges();
		// Set the color for the background
		GraphicsDevice::Main.SetBackgroundColor( Color::Black );

		super::Initialize();
	}

	//-------------------------------------------------------------------------------------------------
	void Test3D::LoadContent()
	{
		scene = Content.Load<Scene>("sceneCompleet");
		scene->Lights.push_back(Light(Color::White, Vector3(0, -1, -1)));
		scene->Ambient = Color::Gray;
		AddComponent(scene.get());
		// Init mario
		mario = New<Mario>();
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
		// Set the palette to non-transparent. Since every tile in a tileset retains a pointer to their common palette, it only has to be changed for a single tile.
		tileSet->Tiles[0].Palettes[0]->Transparent = false;
		
		auto &map = GraphicsDevice.BackgroundMemory->Maps[0];
		
		for(int i = 0; i < tileSet->GetTileCount8x8(); ++i)
		{
			auto &tile = tileSet->Tiles[i];
			GraphicsDevice.BackgroundMemory->AddTile(tile);
			map->SetTile(i, ScreenBlockEntry(tile.Identifier));
		}

		super::LoadContent();
	}

	//-------------------------------------------------------------------------------------------------
	void Test3D::CheckCollisions()
	{
		Matrix transform = Matrix::CreateTranslation(mario->position);
		BoundingBox marioBox = mario->Model->Meshes[0].BoundingBox.Transform(transform);

		for (auto &sceneObject : scene->Objects)
		{
			if (sceneObject == mario)
				return;

			Matrix &otherTransform = sceneObject->Transformation;

			for (auto &mesh : sceneObject->Model->Meshes)
			{
				BoundingBox otherBox = mesh.BoundingBox.Transform(otherTransform);

				if (marioBox.Contains(otherBox) != ContainmentType::Disjoint)
				{
					mario->DidCollideWithObject(otherBox);
				}
			}
		}
	}

	//-------------------------------------------------------------------------------------------------
	void Test3D::Update(const GameTime &gameTime)
	{	
		super::Update(gameTime);
		PROFILE_METHOD(T3DUpd);
		CheckCollisions();
	}

	//-------------------------------------------------------------------------------------------------
	void Test3D::Draw(const GameTime &gameTime)
	{
		PROFILE_METHOD(T3DDrw);

		// Clear the render target in a predetermined color
		GraphicsDevice.Clear(ClearOptions::Target, Color::DeepSkyBlue);
		
		GraphicsDevice::Main.Backgrounds[1]->ColorMode = ColorMode::ColorMode256;
		GraphicsDevice::Main.Backgrounds[1]->ShowMapWithIndex(0);

		super::Draw(gameTime);
	}
}