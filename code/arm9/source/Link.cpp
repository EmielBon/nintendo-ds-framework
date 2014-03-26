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

		int dx = 0, dy = 0;
		
		if (!keys.IsKeyHeld(Keys::All))
		{
			Sprite->SubImageIndex = 0;
		}
		if (keys.IsKeyHeld(Keys::Left) ) 
		{
			dx = -1;
			Sprite = spriteSet->Sprites["link_left"];
		}
		if (keys.IsKeyHeld(Keys::Right)) 
		{
			dx =  1;
			Sprite = spriteSet->Sprites["link_right"];
		}
		if (keys.IsKeyHeld(Keys::Up)   ) 
		{
			dy = -1;
			Sprite = spriteSet->Sprites["link_up"];
		}
		if (keys.IsKeyHeld(Keys::Down) ) 
		{
			dy =  1;
			Sprite = spriteSet->Sprites["link_down"];
		}

		if (dx != 0 || dy != 0)
			ImageSpeed = 10;
		else
			ImageSpeed = 0;

		if(!Game.CurrentRoom().Map->CollisionMap->Collision(X + dx + 16, Y + 16))
			X += Math::Random() > 0.8f ? dx : 0;
		if(!Game.CurrentRoom().Map->CollisionMap->Collision(X + 16, Y + dy + 16))
			Y += dy;

		X = Max(X, 0);
		X = Min(X, 256 - 32);
		Y = Max(Y, 0);
		Y = Min(Y, 192 - 32);
		
		Sprite->X = X;
		Sprite->Y = Y;
	}

	void Link::Draw(const GameTime &gameTime)
	{
		// Todo: use GameTime for speed
		if (ImageSpeed != 0 && ++counter >= 60 / ImageSpeed)
		{
			//counter = (counter + 1) % (60 / ImageSpeed);
			counter = 0;
			if (++Sprite->SubImageIndex >= Sprite->SubImages.size())
				Sprite->SubImageIndex = 0;
		}
		if (Sprite)
			GraphicsDevice::Main.ObjectAttributeMemory.DrawSprite(Sprite);
	}
}