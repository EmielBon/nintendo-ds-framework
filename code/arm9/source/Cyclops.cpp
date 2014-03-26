#include "Cyclops.h"
#include "Enemy.h"
#include "Game.h"

namespace Test
{
	using namespace Framework2D;

	Cyclops::Cyclops(Framework2D::Game2D &game ) : super(game)
	{
		spriteName = "enemy_cyclops32x32";
		paletteName = "enemy_cyclops32x32_pal";
		firesBullets = true;
	}
}

