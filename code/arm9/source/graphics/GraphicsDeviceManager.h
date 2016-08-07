#pragma once

#include "core/types.h"

namespace Framework
{
	class GraphicsDeviceManager
	{
	public:

		GraphicsDeviceManager();

		GraphicsDeviceManager(Game *game);

		void ApplyChanges();

	public:

		bool PreferMultiSampling;
		Graphics::GraphicsDevice *GraphicsDevice;

	private:

		Game *game;
	};

	//-------------------------------------------------------------------------------------------------
	inline GraphicsDeviceManager::GraphicsDeviceManager() : GraphicsDevice(NULL), game(NULL)
	{

	}
}