#include "Chicken.h"
#include "Enemy.h"
#include "Game.h"

namespace Test
{
	using namespace Framework2D;

	Chicken::Chicken(Framework2D::Game2D &game) : super(game)
	{
		spriteName = "enemy_chicken32x32";
		paletteName = "enemy_chicken32x32_pal";
		firesBullets = false;
	}
}