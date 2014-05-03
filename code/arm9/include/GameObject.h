#pragma once

#include "DrawableGameComponent.h"
#include "types.h"

namespace Framework2D
{
	class Game2D;

	class GameObject : public DrawableGameComponent
	{
	protected:

		GameObject();

	public:

		virtual void Update(const GameTime &gameTime);

		void DrawSprite(Ptr<Graphics::Sprite> sprite, fx12 x, fx12 y, fx12 subImageIndex);

	public:

		fx12 X, Y;
		fx12 ImageSpeed;
		fx12 ImageIndex;
		Ptr<Graphics::Sprite> Sprite;
		Ptr<Graphics::SpriteSet> SpriteSet;
	};

	inline GameObject::GameObject() : X(0), Y(0), ImageSpeed(1)
	{

	}
}