#pragma once

#include "types.h"
#include "Game.h"
#include "Console.h"

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
	Graphics::Sprite *sprite;
	Ptr<Graphics::SpriteSet> spriteSet;
	fx12 imageIndex;
};