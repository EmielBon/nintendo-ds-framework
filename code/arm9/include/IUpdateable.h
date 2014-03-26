#pragma once

namespace Framework
{
	class GameTime;

	class IUpdateable
	{
	public:

		IUpdateable() : Enabled(true) { }

	public:

		virtual void Update(const GameTime &gameTime) = 0;

		bool Enabled;
	};
}