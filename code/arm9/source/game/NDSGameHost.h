#pragma once

#include "game/IGameHost.h"
#include "core/types.h"

namespace Framework
{
	class NDSGameHost : public IGameHost
	{
	public:

		NDSGameHost(Game *game);

		virtual ~NDSGameHost() { }

		void Initialize();

		void Run();

		void Exit();

	private:

		bool isExiting;
		Game *game;
	};

	//-------------------------------------------------------------------------------------------------
	inline NDSGameHost::NDSGameHost(Game *game) : isExiting(false), game(game)
	{

	}
}