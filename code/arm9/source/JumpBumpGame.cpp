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
JumpBumpGame::JumpBumpGame()
{

}

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
	auto &bg = *GraphicsDevice::Main.Backgrounds[0]; 
	background->CopyToHardwareBackground(bg);
	base::LoadContent();
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::Update(const Framework::GameTime &gameTime)
{
	base::Update(gameTime);
}

//-------------------------------------------------------------------------------------------------
void JumpBumpGame::Draw(const Framework::GameTime &gameTime)
{
	base::Draw(gameTime);
}