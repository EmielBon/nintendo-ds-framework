#include "game/Room.h"
#include "game/GameObject.h"
#include "graphics/GraphicsDevice.h"
#include "graphics/Background.h"
#include "graphics/TiledBackground.h"
#include "graphics/BackgroundMemory.h"

namespace Framework2D
{
	using namespace Graphics;
	using namespace Framework;
	using namespace Test;

	Room::Room()
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
		GraphicsDevice::Main.Backgrounds[0]->ColorMode = ColorMode::ColorMode256;

		for (auto object : objects)
			object->Draw(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void Room::AddObject(Ptr<GameObject> obj)
	{
		objects.push_back(obj);
	}

	//-------------------------------------------------------------------------------------------------
	void Room::SetBackground(int index, TiledBackground *background)
	{
		auto bg = GraphicsDevice::Main.Backgrounds[index];
		sassert(bg, "Hardware background %i not initialized", index);
		bg->ShowMapWithIndex(index);
		bg->SetLayer(index);

		sassert(index >= 0 && index <= 3, "Map index out of bounds");
		background->CopyToHardwareBackground(*bg);
	}
}