#pragma once

#include "Enemy.h"

namespace Framework2D
{
	class Game2D;
}

namespace Test
{
	class ShadowLink : public Test::Enemy
	{
	private:

		using super = Test::Enemy;

	public:

		ShadowLink(Framework2D::Game2D &game);
	};
}
