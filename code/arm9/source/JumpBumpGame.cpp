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

JumpBumpGame* JumpBumpGame::instance = nullptr;

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::Initialize()
{
	Rabbits.push_back(new Rabbit());
	AddComponent(Rabbits[0]);
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::LoadContent()
{
	base::LoadContent();

	auto background = ContentManager::Load<TiledBackground>("jumpnbumplevel2");
	auto size       = background->Size;
	
	GraphicsDevice::Main.SetBackground(0, *background);
	
	/*for (int x = 0; x < size.Width / 2; ++x)
	for (int y = 0; y < size.Height / 2; ++y)
	{
		int i = x * 2 + size.Width * y * 2;
		auto index = background->TileParameters[i].TileIndex();
		if (index != 0)
			Blocks.push_back(BoundingBox(Vector3(x * 16, y * 16, 0), Vector3(x * 16 + 16, y * 16 + 16, 0)));
	}		*/
	
	auto top    = BoundingBox(Vector3(0, -1, 0), Vector3(256, 0, 0));
	auto bottom = BoundingBox(Vector3(0, 192, 0), Vector3(256, 193, 0));
	auto left   = BoundingBox(Vector3(-1, 0, 0), Vector3(0, 191, 0));
	auto right  = BoundingBox(Vector3(256, 0, 0), Vector3(257, 191, 0));
	
	Blocks.push_back(top);
	Blocks.push_back(bottom);
	Blocks.push_back(left);
	Blocks.push_back(right);
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::CheckCollisions()
{
	for (auto &block : Blocks)
	{
		if (Rabbits[0]->BoundingBox.Contains(block) != ContainmentType::Disjoint)
		{
			Rabbits[0]->DidCollideWithObject(block);
		}
	}
}

bool JumpBumpGame::IsSpaceFree(const BoundingBox &bbox)
{
	for (auto &block : Blocks)
		if (bbox.Contains(block) != ContainmentType::Disjoint)
			return true;
	return false;
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::Update(const Framework::GameTime &gameTime)
{
	CheckCollisions();
	base::Update(gameTime);
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::Draw(const Framework::GameTime &gameTime)
{
	base::Draw(gameTime);
}