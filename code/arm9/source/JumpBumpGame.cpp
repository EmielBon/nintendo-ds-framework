#include "JumpBumpGame.h"

#include "Sprites.h"
#include "ContentManager.h"
#include "Rabbit.h"
#include "GraphicsDevice.h"
#include "ObjectAttributeMemory.h"
#include "Input.h"
#include "TiledBackground.h"
#include "Background.h"

using namespace Framework;
using namespace Graphics;
using namespace Input;

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::Initialize()
{
	Rabbits.push_back(new Rabbit());
	Components.Add(Rabbits[0]);
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::LoadContent()
{
	auto background = ContentManager::Load<TiledBackground>("jumpnbumplevel");
	auto bg = GraphicsDevice::Main.Backgrounds[0];
	background->CopyToHardwareBackground(*bg);
	base::LoadContent();

	auto size = background->Size;

	for (int x = 0; x < size.Width / 2; ++x)
	for (int y = 0; y < size.Height / 2; ++y)
	{
		int i = x * 2 + size.Width * y * 2;
		auto index = background->TileParameters[i].TileIndex();
		if (index != 0)
			Blocks.push_back(BoundingBox(Vector3(x * 16, y * 16, 0), Vector3(x * 16 + 16, y * 16 + 16, 0)));
	}		
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::CheckCollisions()
{
	for (auto &block : Blocks)
		if (Rabbits[0]->BoundingBox.Contains(block) != ContainmentType::Disjoint)
			Rabbits[0]->DidCollideWithObject(block);
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::Update(const Framework::GameTime &gameTime)
{
	base::Update(gameTime);
	CheckCollisions();
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::Draw(const Framework::GameTime &gameTime)
{
	base::Draw(gameTime);
}