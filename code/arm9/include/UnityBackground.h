#pragma once

#include "UnityComponent.h"
#include "TiledBackground.h"

namespace Unity
{
	class TiledBackground : Component
	{
	public:

		void Start();

		void OnDestroy();

	protected:

		Graphics::TiledBackground *tiledBackground;
	};

	inline void TiledBackground::Start()
	{
		// load background resource
	}

	inline void TiledBackground::OnDestroy()
	{
		// unload background resource
	}
}