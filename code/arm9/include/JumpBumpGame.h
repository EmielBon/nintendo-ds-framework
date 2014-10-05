#pragma once

#include "Game.h"
#include "types.h"

class Rabbit;

class JumpBumpGame : public Framework::Game
{
private:

	using base = Framework::Game;

public:

	void Initialize();

	void LoadContent();

	void Update(const Framework::GameTime &gameTime);

	void Draw(const Framework::GameTime &gameTime);

	void CheckCollisions();

public:

	List<Rabbit*> Rabbits;
	List<Framework::BoundingBox> Blocks;
};