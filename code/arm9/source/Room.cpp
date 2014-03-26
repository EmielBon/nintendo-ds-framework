#include "Room.h"
#include "Game2D.h"
#include "GameObject.h"
#include "GraphicsDevice.h"
#include "Background.h"

namespace Framework2D
{
	using namespace Graphics;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	Room::Room(const String &name, Framework2D::Game2D &game) : Name(name), Game(game)
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
		auto &map = GraphicsDevice::Main.BackgroundMemory.Maps[0];

		for(int i = 0; i < Map->GetSize().Width; ++i)
		for(int j = 0; j < Map->GetSize().Height; ++j)
			map.SetTile(i, j, Map->GetTile(i, j));

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
		GraphicsDevice::Main.Background0.ShowMap(0);

		for (auto object : objects)
			object->Draw(gameTime);
	}
}