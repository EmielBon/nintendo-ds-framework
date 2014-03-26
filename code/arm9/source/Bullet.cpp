#include "Bullet.h"
#include "Game2D.h"
#include "MathFunctions.h"
#include "GameObject.h"
#include "GraphicsDevice.h"
#include "ObjectAttributeMemory.h"
#include "TileSet256.h"
#include "Sprite.h"
#include "Vec2.h"
#include "ContentManager.h"

namespace Test
{
	using namespace std;
	using namespace Math;
	using namespace Graphics;
	using namespace Framework;
	using namespace Framework2D;

	Bullet::Bullet(Framework2D::Game2D &game, fx12 x, fx12 y) : super(game), X(x), Y(y), dx(0), dy(0)
	{
		
	}

	void Bullet::Initialize()
	{
		targetX = 15;
		targetY = 15;
		DirectAtTarget();
	}

	void Bullet::LoadContent()
	{
		Ptr<Graphics::TileSet256> spriteSheet = ContentManager::Load<TileSet256>("bullet32x32");
		spriteSheet->SetPalette(ContentManager::Load<Palette>("bullet32x32_pal"));

		u32 animation[] = {0};
		List<u32> subImages (animation, animation + sizeof(animation) / sizeof(u32) );

		//Sprite = New<Graphics::Sprite>(spriteSheet, subImages);
		//Sprite->Scale = 0.5f;
	}

	void Bullet::Update(const GameTime &gameTime)
	{
		X += dx;
		Y += dy;
	}

	void Bullet::Draw(const GameTime &gameTime)
	{
		Sprite->X = (int)X;
		Sprite->Y = (int)Y;

		GraphicsDevice::Main.ObjectAttributeMemory.DrawSprite(Sprite);
	}

	bool Bullet::Collision()
	{
		//return (X < 0 || X > 256 || Y < 0 || Y > 192 ||					// Out of bounds
		//	   (Abs(X - targetX) < 16 && Abs(Y - targetY)< 16));		// Bullet hit Link
	}
	
	void Bullet::SetDirection(fx12 dx, fx12 dy)
	{
		this->dx = dx;
		this->dy = dy;
	}

	fx12 Bullet::DistanceToTarget()
	{
		Vector2 dist(targetX - X, targetY - Y);
		return dist.Length();
	}

	void Bullet::DirectAtTarget()
	{
		fx12 distance = DistanceToTarget();
		SetDirection( 2 * (targetX - X) / distance, 2 * (targetY - Y) / distance );
	}
}