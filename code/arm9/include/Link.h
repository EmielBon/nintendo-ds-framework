#pragma once

#include "GameObject.h"
#include "types.h"

namespace Test
{
	class Link : public Framework2D::GameObject
	{
	private:

		using super = Framework2D::GameObject;

	public:

		Link(Framework2D::Game2D &game);

	public:

		void Initialize();

		void LoadContent();

		void Update(const GameTime &gameTime);

		void Draw(const GameTime &gameTime);

	private:

		int counter;
		Ptr<SpriteSet> spriteSet;
	};
}