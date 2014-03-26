#include "Guard.h"
#include "Enemy.h"
#include "Game.h"

namespace Test
{
	Guard::Guard(Framework2D::Game2D &game) : super(game)
	{
		spriteName = "enemy_guard32x32";
		paletteName = "enemy_guard32x32_pal";
		firesBullets =false;
	}
}
