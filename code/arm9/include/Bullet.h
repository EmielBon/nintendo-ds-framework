#pragma once

#include "GameObject.h"
#include "IGameComponent.h"
#include "fixed.h"

namespace Framework
{
	class Game2D;
}

namespace Test
{
	class Bullet : public Framework2D::GameObject
	{
	public:

		using super = Framework2D::GameObject;

	public:

		Bullet(Framework2D::Game2D &game, fx12 x, fx12 y);
		
		void Initialize();

		void LoadContent();

		void Update(const GameTime &gameTime);

		void Draw(const GameTime &gameTime);

		void SetDirection(fx12 dx, fx12 dy);

		bool Collision();

	private:

		fx12 DistanceToTarget();

		void DirectAtTarget();

	public:

		fx12 X, Y;
		int targetX, targetY;

	private:

		fx12 dx, dy;
	};
}