#include "Rabbit.h"
#include "Input.h"
#include "ContentManager.h"

using namespace Framework;
using namespace Input;

void Rabbit::LoadContent()
{
	Sprites = ContentManager::Load<SpriteSet>("rabbit").get();
	CurrentSprite = (*Sprites)["rabbit_walk"];
	x = 50;
	y = 50;
}

void Rabbit::Update(const GameTime &gameTime)
{
	fx12 timeStep = gameTime.ElapsedGameTime.TotalSeconds();
	int speed = 64;

	auto keys = KeyPad::GetState();
	auto direction = keys.GetDirectionalPadVector();
	x += direction.x * speed * timeStep;
	y += -direction.y * speed * timeStep;
}

void Rabbit::Draw(const GameTime &gameTime)
{
	fx12 imageIndex = gameTime.TotalGameTime.TotalSeconds() * 8;
	GraphicsDevice::Main.DrawSprite(*CurrentSprite, x, y, imageIndex);
}