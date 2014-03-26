#pragma once

#include "Enemy.h"

namespace Framework2D
{
	class Game2D;
}

namespace Test
{
	class Chicken : public Test::Enemy
	{
	private:

		using super = Test::Enemy;

	public:

		Chicken(Framework2D::Game2D &game);
	};
}
