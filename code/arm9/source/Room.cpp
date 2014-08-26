#include "Room.h"
#include "GameObject.h"
#include "GraphicsDevice.h"
#include "Background.h"
#include "TiledBackground.h"

namespace Framework2D
{
	using namespace Graphics;
	using namespace Framework;
	using namespace Test;

	Room::Room()
		: Background0(Graphics::GraphicsDevice::Main.Background0),
		  Background1(Graphics::GraphicsDevice::Main.Background1),
		  Background2(Graphics::GraphicsDevice::Main.Background2),
		  Background3(Graphics::GraphicsDevice::Main.Background3)
	{

	}

	//-------------------------------------------------------------------------------------------------
	void Room::Initialize()
	{
		for (auto object : objects)
			object->Initialize();
	}

	//-------------------------------------------------------------------------------------------------
	void Room::LoadContent()
	{
		for (auto object : objects)
			object->LoadContent();
	}

	//-------------------------------------------------------------------------------------------------
	void Room::Update(const GameTime &gameTime)
	{
		for (auto object : objects)
			object->Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void Room::Draw(const GameTime &gameTime)
	{
		GraphicsDevice::Main.Background0.ColorMode = ColorMode::ColorMode256;

		for (auto object : objects)
			object->Draw(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void Room::AddObject(Ptr<GameObject> obj)
	{
		objects.push_back(obj);
	}

	//-------------------------------------------------------------------------------------------------
	void Room::SetBackground(int index, Ptr<TiledBackground> background)
	{
		Background *bg = nullptr;

		switch (index)
		{
		case 0: bg = &Background0; break;
		case 1: bg = &Background1; break;
		case 2: bg = &Background2; break;
		case 3: bg = &Background3; break;
		default: CRASH("Background index out of range [0..3] for index (" << index << ")"); break;
		}
	
		background->CopyToHardwareMap(*bg->GetMap());
		bg->ShowMap(index);
		bg->Enable();
		bg->SetLayer(index);
	}
}