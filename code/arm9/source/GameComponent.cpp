#include "GameComponent.h"
#include "Debug.h"
namespace Framework
{
	//-------------------------------------------------------------------------------------------------
	void GameComponent::Initialize()
	{
		for (auto it = Components.begin(); it != Components.end(); ++it)
		{
			(*it)->Initialize();
		}
		Initialized = true;
	}

	//-------------------------------------------------------------------------------------------------
	void GameComponent::Update(const GameTime &gameTime)
	{
		for (auto it = Components.begin(); it != Components.end(); ++it)
		{
			GameComponent *component = *it;

			if (!component->Initialized)
				component->Initialize();

			if (component->Enabled)
				component->Update(gameTime);
		}
	}
}