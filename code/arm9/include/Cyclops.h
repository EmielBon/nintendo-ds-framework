#pragma once

#include "Enemy.h"

namespace Framework2D
{
	class Game2D;
}
namespace Test
{
	class Cyclops : public Test::Enemy
	{
	private:

		using super = Test::Enemy;

	public:
		
		Cyclops(Framework2D::Game2D &game);
	};
}
