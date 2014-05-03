#include "Room1.h"
#include "ContentManager.h"
#include "TiledBackground.h"

namespace Test
{
	void Room1::Initialize()
	{
		link = New<Link>();
		objects.push_back(link);

		link->X = 128 -16;
		link->Y = 96 - 16;

		auto map = ContentManager::Load<TiledBackground>("newGameMap1");
		map->CopyToHardwareMap(0);
		Background0.ShowMap(0);
		Background0.Enable();
		Background0.SetLayer(0);

		base::Initialize();
	}

	void Room1::Update(const GameTime &gameTime)
	{
		base::Update(gameTime);
	}

}