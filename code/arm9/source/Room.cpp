#include "Room.h"
#include "GameObject.h"
#include "GraphicsDevice.h"
#include "Background.h"
#include "Link.h"

namespace Framework2D
{
	using namespace Graphics;
	using namespace Framework;
	using namespace Test;

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
}