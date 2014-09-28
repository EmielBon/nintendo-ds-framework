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
	Rabbits.push_back(new Rabbit());
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::LoadContent()
{

}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::Update(const Framework::GameTime &gameTime)
{
	auto &spriteSet = *ContentManager::Load<SpriteSet>("rabbit");
	Rabbits[0]->Sprite = spriteSet["rabbit_walk"];
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::Draw(const Framework::GameTime &gameTime)
{
	fx12 imageIndex = gameTime.TotalGameTime.TotalSeconds() * 8;
	GraphicsDevice::Main.DrawSprite(*Rabbits[0]->Sprite, 0, 0, imageIndex);
}