#pragma once

#include "Enemy.h"

namespace Framework2D
{
	class Game2D;
}

namespace Test
{
	class Guard : public Test::Enemy
	{
	private:

		using super = Test::Enemy;

	public:

		Guard(Framework2D::Game2D &game);
	};
}
