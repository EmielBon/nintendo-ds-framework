#include "GraphicsDeviceManager.h"
#include "Game.h"
#include <nds/arm9/videoGL.h>

namespace Framework
{
	//-------------------------------------------------------------------------------------------------
	GraphicsDeviceManager::GraphicsDeviceManager(Game *game) : GraphicsDevice(&game->GraphicsDevice), game(game)
	{

	}

	//-------------------------------------------------------------------------------------------------
	void GraphicsDeviceManager::ApplyChanges()
	{
		if (PreferMultiSampling)
			glEnable(GL_ANTIALIAS);
		else 
			glDisable(GL_ANTIALIAS);
	}

}