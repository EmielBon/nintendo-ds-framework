#pragma once

#include "Game.h"

namespace Test
{
	class SpriteTest : public Game
	{
	private:
		
		using super = Framework::Game;
	
	protected:
	 
		void Initialize();
		void LoadContent();
		void Update(const GameTime &gameTime);
		void Draw(const GameTime &gameTime);

	public:

		Ptr<Sprite> sprite;
	};
}