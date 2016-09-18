/*#pragma once

#include "Game.h"
#include "types.h"

class Rabbit;

class JumpBumpGame : public Framework::Game
{
private:

	using base = Framework::Game;

public:

	JumpBumpGame();

	static JumpBumpGame &Instance();

	void Initialize();

	void LoadContent();

	void Update(const Framework::GameTime &gameTime);

	void Draw(const Framework::GameTime &gameTime);

	void CheckCollisions();

	bool IsSpaceFree(const Framework::BoundingBox &bbox);

public:

	List<Rabbit*> Rabbits;
	List<Framework::BoundingBox> Blocks;
	static JumpBumpGame *instance;
};

inline JumpBumpGame::JumpBumpGame()
{
	instance = this;
}

inline JumpBumpGame& JumpBumpGame::Instance()
{
	return *instance;
}*/
