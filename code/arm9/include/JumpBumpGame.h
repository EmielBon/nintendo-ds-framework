#pragma once

#include "Game.h"
#include "types.h"

class Rabbit;

class JumpBumpGame : public Framework::Game
{
public:

	JumpBumpGame();

	void Initialize();

	void LoadContent();

	void Update(const Framework::GameTime &gameTime);

	void Draw(const Framework::GameTime &gameTime);

public:

	List<Rabbit*> Rabbits;
};