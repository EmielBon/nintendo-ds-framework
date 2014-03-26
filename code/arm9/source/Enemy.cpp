#include "Enemy.h"

// Stable libraries
#include "types.h"
#include "Framework2D.h"
#include "MathFunctions.h"

// Specific libraries
#include "GraphicsDevice.h"
#include "Sprite.h"
#include "ObjectAttributeMemory.h"
#include "TileSet256.h"
#include "GameTime.h"

// Game stuff
#include "Bullet.h"
#include "Link.h"

namespace Test
{
	using namespace Graphics;
	using namespace Framework;
	using namespace Framework2D;

	Enemy::Enemy(Framework2D::Game2D &game) : super(game)
	{
	}

	void Enemy::Initialize()
	{
		if(firesBullets)
		{
			bullet2 = New<Bullet>(Game, X, Y);
			bullet2->Initialize();
		}

		currentIndex = 0;
	}

	void Enemy::Update(const GameTime &gameTime)
	{
		CalculateDirection();

		X += dx * 20 * (fx12)gameTime.ElapsedGameTime.TotalSeconds();
		Y += dy * 20 * (fx12)gameTime.ElapsedGameTime.TotalSeconds();

		if(firesBullets)
		{
			if(bullet2->Collision())
			{
				bullet2 = New<Bullet>(Game, X, Y);								
				bullet2->Initialize();	
				bullet2->LoadContent();
			}	
			else
				bullet2->Update(gameTime);
		}
	}

	void Enemy::Draw(const GameTime &gameTime)
	{
		Sprite->X = (int)X;
		Sprite->Y = (int)Y;
		GraphicsDevice::Main.ObjectAttributeMemory.DrawSprite(Sprite);

		if(firesBullets)
			bullet2->Draw(gameTime);
	}

	void Enemy::LoadContent()
	{
		/*Ptr<Graphics::TileSet256> spriteSheet = ContentManager::Load<Graphics::TileSet256>(spriteName);
		spriteSheet->SetPalette(ContentManager::Load<Palette>(paletteName));
		u32 animation[] = {0};
		List<u32> subImages (animation, animation + sizeof(animation) / sizeof(u32) );
		Sprite = New<Graphics::Sprite>(spriteSheet, subImages);

		if(firesBullets)
			bullet2->LoadContent();*/
	}

	void Enemy::CalculateDirection()
	{
		auto target = (*path)[currentIndex];
		if((int)X == std::get<0>(target) * 16 && (int)Y == std::get<1>(target) * 16)
		{
			currentIndex = (currentIndex + 1) % path->Size();
			target = (*path)[currentIndex];
		}
		dx = Math::Sign(std::get<0>(target) * 16 - X);
		dy = Math::Sign(std::get<1>(target) * 16 - Y);
	}
}