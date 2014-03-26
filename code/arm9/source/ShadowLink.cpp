#include "ShadowLink.h"
#include "Enemy.h"
#include "Game.h"

namespace Test
{
	ShadowLink::ShadowLink(Framework2D::Game2D &game) : super(game)
	{
		spriteName = "enemy32x32";
		paletteName = "enemy32x32_pal";
		firesBullets = true;
	}
}
