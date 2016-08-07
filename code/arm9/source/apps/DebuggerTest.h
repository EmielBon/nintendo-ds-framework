#pragma once

#include "core/types.h"
#include "game/Game.h"
#include "debug/Console.h"

class DebuggerTest : public Framework::Game
{
private:

	using super = Framework::Game;

protected:

	void Initialize();
	void LoadContent();
	void Update(const Framework::GameTime &gameTime);
	void Draw(const Framework::GameTime &gameTime);

public:

	System::Console *console;
};