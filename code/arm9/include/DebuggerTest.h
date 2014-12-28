#pragma once

#include "types.h"
#include "Game.h"

class DebuggerTest : public Framework::Game
{
private:

	using super = Framework::Game;

protected:

	void Initialize();
	void LoadContent();
	void Update(const Framework::GameTime &gameTime);
	void Draw(const Framework::GameTime &gameTime);
};