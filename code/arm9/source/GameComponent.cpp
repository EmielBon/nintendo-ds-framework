#include "GameComponent.h"
#include "Debug.h"
namespace Framework
{
	//-------------------------------------------------------------------------------------------------
	void GameComponent::Initialize()
	{
		for (auto &component : Components)
		{
			component->Initialize();
		}
		Initialized = true;
	}

	//-------------------------------------------------------------------------------------------------
	void GameComponent::Update(const GameTime &gameTime)
	{
		for (auto &component : Components)
		{
			if (!component->Initialized)
				component->Initialize();

			if (component->Enabled)
				component->Update(gameTime);
		}
	}
}