#pragma once

namespace Framework
{
	class IGameHost
	{
	public:

		//virtual GameWindow& Window() = 0;

		//virtual void EnsureHost() = 0;

		virtual void Initialize() = 0;

		virtual void Run() = 0;

		virtual void Exit() = 0;
	};
}