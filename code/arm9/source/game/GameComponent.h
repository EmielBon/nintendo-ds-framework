#pragma once

#include "game/IGameComponent.h"
#include "game/IUpdateable.h"
#include "game/IDisposable.h"
#include "core/types.h"

namespace Framework
{
	class GameTime;

	class GameComponent : public IGameComponent, public IUpdateable, public IDisposable
	{
	public:

		GameComponent() : Initialized(false) { Enabled = true; };
		virtual ~GameComponent() = default;
		virtual void Initialize();
		virtual void Update(const GameTime &gameTime);
		virtual void Dispose() { };

	protected:

		bool Initialized;

	public:

		Set<GameComponent *> Components;
	};
}
