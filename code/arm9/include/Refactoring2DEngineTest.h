#pragma once

#include "types.h"
#include "Game.h"
#include "Console.h"
#include "Sprite.h"

class Refactoring2DEngineTest : public Framework::Game
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
	Graphics::Sprite sprite;
	Graphics::Sprite chomp;
	fx12 imageIndex;
	float rotation;
	float x;
};
