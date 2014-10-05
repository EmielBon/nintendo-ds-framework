#include "Rabbit.h"
#include "Input.h"
#include "ContentManager.h"

using namespace Framework;
using namespace Input;

void Rabbit::LoadContent()
{
	Sprites = ContentManager::Load<SpriteSet>("rabbit").get();
	CurrentSprite = (*Sprites)["rabbit_walk"];
	Position = Vector2(50, 50);
	BoundingBox = Framework::BoundingBox(Vector3::Zero(), Vector3(16, 16, 0));
	gravity = 256.0f;
	scale = 1;
}

void Rabbit::DidCollideWithObject(const Framework::BoundingBox &bbox)
{
	if (bbox.Contains(BoundingBox.Center() + Vector3(0, BoundingBox.GetHeight() / 2 + 1, 0)) == ContainmentType::Contains)
	{
		Position.y = bbox.Min.y - BoundingBox.GetHeight();
		speed.y = 0;
	}
	else if (bbox.Contains(BoundingBox.Center() - Vector3(0, BoundingBox.GetHeight() / 2 - 1, 0)) == ContainmentType::Contains)
	{
		Position.y = bbox.Max.y;
		speed.y = 0;
	}
	else if (bbox.Contains(BoundingBox.Center() + Vector3(BoundingBox.GetWidth() / 2 + 1, 0, 0)) == ContainmentType::Contains)
	{
		Position.x = bbox.Min.x - BoundingBox.GetWidth();
		speed.x = 0;
	}
	else if (bbox.Contains(BoundingBox.Center() - Vector3(BoundingBox.GetWidth() / 2 - 1, 0, 0)) == ContainmentType::Contains)
	{
		Position.x = bbox.Max.x;
		speed.x = 0;
	}
}

void Rabbit::Update(const GameTime &gameTime)
{
	fx12 maxHorizontalSpeed = 64;
	fx12 maxVerticalSpeed = 64;
	fx12 jumpSpeed = 164;

	fx12 timeStep = gameTime.ElapsedGameTime.TotalSeconds();

	auto keys = KeyPad::GetState();
	auto direction = keys.GetDirectionalPadVector();
	if (keys.IsKeyPressed(Keys::Up) && speed.y == 0)
	{
		speed.y = -jumpSpeed;
		gravity = 256.0f;
	}

	speed.x = direction.x * maxHorizontalSpeed;
	speed.y += gravity * timeStep;
	

	//Position = PlaceFree(Position, speed, BoundingBox);
	Position += speed * timeStep;

	if (Position.y >= 176)
	{
		Position.y = 176;
		speed.y = 0;
	}

	scale = (direction.x == 0) ? scale : direction.x;

	BoundingBox.Min = Vector3(Position.x, Position.y, 0);
	BoundingBox.Max = Vector3(Position.x + 16, Position.y + 16, 0);
}

void Rabbit::Draw(const GameTime &gameTime)
{
	fx12 imageIndex = gameTime.TotalGameTime.TotalSeconds() * 8;
	GraphicsDevice::Main.DrawSprite(*CurrentSprite, Position.x, Position.y, imageIndex, scale, 1);
}