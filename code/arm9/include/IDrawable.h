#pragma once

namespace Framework
{
	class IDrawable
	{
	public:

		IDrawable() : Visible(true) { }

	public:

		virtual void Draw(const GameTime &gameTime) = 0;

		bool Visible;
	};
}