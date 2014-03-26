#pragma once

#include "IGameComponent.h"
#include "IUpdateable.h"
#include "IDisposable.h"

namespace Framework
{
	class GameTime;

	class GameComponent : public IGameComponent, public IUpdateable, public IDisposable
	{
	public:

		GameComponent() { Enabled = true; };
		virtual ~GameComponent() { };
		virtual void Initialize() { };
		virtual void Update(const GameTime &gameTime) { };
		virtual void Dispose() { };
	};
}