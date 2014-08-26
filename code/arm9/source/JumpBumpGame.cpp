#include "JumpBumpGame.h"

#include "Sprites.h"
#include "ContentManager.h"
#include "Rabbit.h"
#include "GraphicsDevice.h"
#include "ObjectAttributeMemory.h"

using namespace Framework;
using namespace Graphics;

//-------------------------------------------------------------------------------------------------
JumpBumpGame::JumpBumpGame()
{

}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::Initialize()
{
	Rabbits.push_back(New<Rabbit>());
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::LoadContent()
{
	auto spriteSet = ContentManager::Load<SpriteSet>("rabbit");
	for (auto sprite : spriteSet->Sprites)
		GraphicsDevice::Main.SpriteMemory->AddSprite(*sprite.second);
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::Update(const Framework::GameTime &gameTime)
{
	auto spriteSet = ContentManager::Load<SpriteSet>("rabbit");
	Rabbits[0]->Sprite = (*spriteSet)["rabbit_walk"];
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::Draw(const Framework::GameTime &gameTime)
{
	GraphicsDevice::Main.ObjectAttributeMemory.DrawSprite(Rabbits[0]->Sprite, 0, 0, (int)(gameTime.TotalGameTime.TotalSeconds() * 8) % 4);
}