#pragma once

#include "types.h"
#include "UnityComponent.h"

namespace Unity
{
	class ComponentContainer
	{
	public:

		template<class T>
		T* GetComponent<T>();

		void AddComponent(Component *component);

		// RemoveComponent()

	public:

		List<Component *> Components;
	};

	void ComponentContainer::AddComponent(Component *component)
	{
		Components.push_back(component);
	}

	template<class T>
	inline T* GetComponent()
	{
		T* comp = nullptr;

		for (auto &component : Components)
		{
			comp = dynamic_cast<T*>(component);
			if (comp)
				return comp;
		}

		sassert(comp, "Error: No component with specified type found");
		return comp;
	}
}