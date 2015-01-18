#include "DrawableGameComponent.h"

namespace Framework
{
	//-------------------------------------------------------------------------------------------------
	void DrawableGameComponent::LoadContent()
	{

		for (auto it = Components.begin(); it != Components.end(); ++it)
		{
			if (auto drawable = static_cast<DrawableGameComponent*>(*it))
			{
				drawable->LoadContent();
			}
		}
		ContentLoaded = true;
	}

	//-------------------------------------------------------------------------------------------------
	void DrawableGameComponent::Draw(const GameTime &gameTime)
	{
		for (auto it = Components.begin(); it != Components.end(); ++it)
		{
			if (auto drawable = dynamic_cast<DrawableGameComponent*>(*it))
			{
				if (!drawable->ContentLoaded)
					drawable->LoadContent();

				if (drawable->Visible)
					drawable->Draw(gameTime);
			}
		}
	}
}