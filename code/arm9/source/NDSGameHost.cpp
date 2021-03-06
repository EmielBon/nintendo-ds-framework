#include "NDSGameHost.h"

#include "Game.h"

namespace Framework
{
	//-------------------------------------------------------------------------------------------------
	void NDSGameHost::Initialize()
	{

	}

	//-------------------------------------------------------------------------------------------------
	void NDSGameHost::Run()
	{
		while (!isExiting)
		{                            
			game->Tick();
		}
	}

	//-------------------------------------------------------------------------------------------------
	void NDSGameHost::Exit()
	{
		isExiting = true;
	}
}