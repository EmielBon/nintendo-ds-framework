#pragma once

#include "types.h"
#include "ComponentContainer.h"

namespace Unity
{
	class GameObject : ComponentContainer
	{
	public:

		static GameObject* Create(const String &tag);

	protected:

		GameObject(const String &tag);

	public:

		String Tag;

	private:

		static Dictionary<String, List<GameObject>> GameObjectLibrary;
	};

	inline GameObject::GameObject(const String &tag)
	{
		Tag = tag;
		// add transform
	}

	inline GameObject* GameObject::Create(const String &tag)
	{
		GameObjectLibrary[tag].push_back( GameObject(tag) );
	}
}