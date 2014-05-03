#pragma once

#include "GameObject.h"
#include "types.h"

namespace Test
{
	class Link : public Framework2D::GameObject
	{
	private:

		using base = Framework2D::GameObject;

	public:

		void Initialize();

		void LoadContent();

		void Update(const GameTime &gameTime);

		void Draw(const GameTime &gameTime);
	};
}