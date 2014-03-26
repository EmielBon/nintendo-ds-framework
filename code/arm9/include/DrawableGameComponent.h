#pragma once

#include "GameComponent.h"
#include "IDrawable.h"

namespace Framework
{
	class GameTime;

	class DrawableGameComponent : public GameComponent, public IDrawable
	{
	public:

		DrawableGameComponent() { Visible = true; };
		virtual ~DrawableGameComponent() { };
		virtual void Initialize() { };
		virtual void LoadContent() { };
		virtual void Update(const GameTime &gameTime) { };
		virtual void Draw(const GameTime &gameTime) { };
		virtual void UnloadContent() { };
		virtual void Dispose() { };
	};
}