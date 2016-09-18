/*#include "Rabbit.h"
#include "Input.h"
#include "ContentManager.h"
#include "Range.h"
#include "JumpBumpGame.h"

using namespace Framework;
using namespace Input;

void Rabbit::Initialize()
{
	base::Initialize();

	Position = Vector2(50, 50);
	gravity = 256.0f;
	scale = 1;

	BoundingBox = Framework::BoundingBox(Vector3::Zero(), Vector3(16, 16, 0));


}

void Rabbit::LoadContent()
{
	Sprites = ContentManager::Load<SpriteSet>("rabbit").get();
	CurrentSprite = (*Sprites)["rabbit_walk"];

	base::LoadContent();
}

void Rabbit::DidCollideWithObject(const Framework::BoundingBox &bbox)
{
	Vector3 halfway = Vector3::Sign(BoundingBox.Center() - bbox.Center());

	Range horA = {BoundingBox.Min.x, BoundingBox.Max.x};
	Range horB = {bbox.Min.x,        bbox.Max.x };

	Range verA = { BoundingBox.Min.y, BoundingBox.Max.y };
	Range verB = { bbox.Min.y, bbox.Max.y };

	fx12 horOverlap = horA.Overlap(horB);
	fx12 verOverlap = verA.Overlap(verB);

	if (horOverlap < 0.01f || verOverlap < 0.1f) return;

	Vector3 displacement = halfway * Vector3(horOverlap, verOverlap, 0);

	if (horOverlap < verOverlap )
	{
		Position.x += displacement.x;
		speed.x = 0;
	}
	else
	{
		Position.y += displacement.y;
		speed.y = 0;
	}
}

void Rabbit::Update(const GameTime &gameTime)
{
	fx12 maxHorizontalSpeed = 80;
	fx12 maxVerticalSpeed = 64;
	fx12 jumpSpeed = 164;

	fx12 timeStep = gameTime.ElapsedGameTime.TotalSeconds();

	auto keys = KeyPad::GetState();
	auto direction = keys.GetDirectionalPadVector();

	auto bbox = BoundingBox;
	bbox.Min.y += 1;
	bbox.Max.y += 1;

	if (keys.IsKeyPressed(Keys::Up) && (JumpBumpGame::Instance().IsSpaceFree(bbox) || Position.y >= 176))
	{
		speed.y = -jumpSpeed;
	}

	speed.x = direction.x * maxHorizontalSpeed;
	speed.y += gravity * timeStep;

	Position += speed * timeStep;

	if (Position.y >= 176)
	{
		Position.y = 176;
		speed.y = 0;
	}

	scale = (direction.x == 0) ? scale : direction.x;

	BoundingBox.Min = Vector3(Position.x, Position.y, 0);
	BoundingBox.Max = Vector3(Position.x + 16, Position.y + 16, 0);

	base::Update(gameTime);
}

void Rabbit::Draw(const GameTime &gameTime)
{
	fx12 imageIndex = gameTime.TotalGameTime.TotalSeconds() * 8;
	GraphicsDevice::Main.DrawSprite(*CurrentSprite, Position.x, Position.y, imageIndex, scale, 1);

	base::Draw(gameTime);
}*/
