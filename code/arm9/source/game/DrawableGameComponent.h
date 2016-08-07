#pragma once

#include "game/GameComponent.h"
#include "game/IDrawable.h"

namespace Framework
{
	class GameTime;

	class DrawableGameComponent : public GameComponent, public IDrawable
	{
	public:

		DrawableGameComponent() : ContentLoaded(false) { Visible = true; };
		virtual ~DrawableGameComponent() = default;
		//virtual void Initialize();
		virtual void LoadContent();
		//virtual void Update(const GameTime &gameTime);
		virtual void Draw(const GameTime &gameTime);
		virtual void UnloadContent() { };
		virtual void Dispose() { };

	protected:

		bool ContentLoaded;
	};
}