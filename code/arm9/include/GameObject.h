#pragma once

#include "DrawableGameComponent.h"
#include "types.h"

namespace Framework2D
{
	class Game2D;

	class GameObject : public Framework::DrawableGameComponent
	{
	protected:

		GameObject(Framework2D::Game2D &game);

	public:

		int X, Y;
		int ImageSpeed;
		Ptr<Graphics::Sprite> Sprite;

	protected:

		Framework2D::Game2D &Game;
	};

	inline GameObject::GameObject(Framework2D::Game2D &game) : X(0), Y(0), ImageSpeed(1), Game(game)
	{

	}
}