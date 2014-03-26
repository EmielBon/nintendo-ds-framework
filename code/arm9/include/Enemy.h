#pragma once

#include "Game.h"
#include "GameObject.h"
#include "Link.h"
#include "Bullet.h"
#include "Path.h"

namespace Framework2D
{
	class Game2D;
}

namespace Test
{
	class Enemy : public Framework2D::GameObject
	{
	private:

		using super = Framework2D::GameObject;

	public:
		
		Enemy(Framework2D::Game2D &game);
	
	public:

		void Initialize();

		void LoadContent();

		void Update(const GameTime &gameTime);

		void Draw(const GameTime &gameTime);

	public:

		void AddPathCoordinates();

		void CalculateDirection();

	public:

		fx12 X, Y;
		fx12 dx, dy;
		int currentIndex;
		Ptr<Bullet> bullet2;
		Ptr<Framework2D::Path> path;
		String spriteName, paletteName;
		bool firesBullets;
	};
}