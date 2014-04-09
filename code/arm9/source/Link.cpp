#include "Link.h"

#include "Game2D.h"
#include "Room.h"
#include "TiledBackground.h"
#include "CollisionMap.h"
#include "GraphicsDevice.h"
#include "ObjectAttributeMemory.h"
#include "TileSet256.h"
#include "MathFunctions.h"
#include "KeyPad.h"
#include "Sprite.h"
#include "SpriteSet.h"

namespace Test
{
	using namespace Math;
	using namespace Input;
	using namespace Graphics;
	using namespace Framework;

	Link::Link(Framework2D::Game2D &game) : super(game)
	{

	}

	void Link::Initialize()
	{
		counter = 0;
	}

	void Link::LoadContent()
	{
		spriteSet = Game.Content.Load<SpriteSet>("link");

		Sprite = spriteSet->Sprites["link_down"];
	}

	void Link::Update(const GameTime &gameTime)
	{
		KeyState keys = KeyPad::GetState();

		fx12 timeStep = gameTime.ElapsedGameTime.TotalSeconds();
		fx12 speed = 96;

		Vector2 direction(0, 0);
		
		if (!keys.IsKeyHeld(Keys::All))
		{
			Sprite->SubImageIndex = 0;
		}
		if (keys.IsKeyHeld(Keys::Left) ) 
		{
			direction.x = -1;
			Sprite = spriteSet->Sprites["link_left"];
		}
		if (keys.IsKeyHeld(Keys::Right)) 
		{
			direction.x = 1;
			Sprite = spriteSet->Sprites["link_right"];
		}
		if (keys.IsKeyHeld(Keys::Up)   ) 
		{
			direction.y = -1;
			Sprite = spriteSet->Sprites["link_up"];
		}
		if (keys.IsKeyHeld(Keys::Down) ) 
		{
			direction.y = 1;
			Sprite = spriteSet->Sprites["link_down"];
		}

		if (direction.LengthSquared() > 0)
			ImageSpeed = 8 * timeStep;
		else
			ImageSpeed = 0;

		direction = direction.Normalize();

		if(!Game.CurrentRoom().Map->CollisionMap->Collision(int(X + direction.x + 16), int(Y + 16)))
			X += direction.x * speed * timeStep;
		if(!Game.CurrentRoom().Map->CollisionMap->Collision(int(X + 16), int(Y + direction.y + 16)))
			Y += direction.y * speed * timeStep;

		X = Max(X, fx12(0));
		X = Min(X, fx12(256 - 32));
		Y = Max(Y, fx12(0));
		Y = Min(Y, fx12(192 - 32));
		
		Sprite->X = (int)X;
		Sprite->Y = (int)Y;
	}

	void Link::Draw(const GameTime &gameTime)
	{
		ImageIndex += ImageSpeed;
		if ((int)ImageIndex >= Sprite->SubImages.size())
			ImageIndex = 0;
		Sprite->SubImageIndex = (int)ImageIndex;

		if (Sprite)
			GraphicsDevice::Main.ObjectAttributeMemory.DrawSprite(Sprite);
	}
}