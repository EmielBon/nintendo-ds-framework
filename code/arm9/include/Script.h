#pragma once

#include "UnityComponent.h"

namespace Unity
{
	class Script : Component
	{
	public:

		virtual void Start();

		virtual void FixedUpdate();

		virtual void Update();

		virtual void OnEnable();

		virtual void OnDisable();

		virtual void OnDestroy();
	};
}