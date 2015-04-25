#pragma once

#include "types.h"
#include "Mat.h"
#include "UnityComponent.h"


namespace Unity
{
	class GameObject;

	class Transform : Component
	{
	public:

		Transform(GameObject *gameObject);

	public:

		Transform *Parent;

		int ChildCount() const;

	private:

		List<Transform *> children;
		Framework::Matrix transform;
		GameObject *gameObject;
	};

	inline Transform::Transform(GameObject *gameObj)
	{
		gameObject = gameObj;
	}

	inline int Transform::ChildCount() const
	{
		return children.size();
	}
}