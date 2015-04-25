#pragma once

namespace Unity
{
	class Component
	{
	public:

		virtual void Start();

		virtual void Update();

		virtual void OnDestroy();

	public:

		bool Enabled;
	};
}