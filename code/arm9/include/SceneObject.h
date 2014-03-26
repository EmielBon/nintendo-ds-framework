#pragma once

#include "DrawableGameComponent.h"
#include "types.h"
#include "Mat.h"

namespace Graphics
{
	class SceneObject : public DrawableGameComponent
	{
	public:

		SceneObject() = default;

		SceneObject(const String& name);

		SceneObject(Ptr<Graphics::Model> model, Matrix transformation, bool solid = false);

		SceneObject(const String& name, Ptr<Graphics::Model> model, Matrix transformation, bool solid = false);

	protected:

		void Draw(const GameTime &gameTime) { };

	public:

		String name;
		Ptr<Graphics::Model> Model;
		Matrix Transformation;
		bool Solid;
	};

	//-------------------------------------------------------------------------------------------------
	inline SceneObject::SceneObject(const String& name) : name(name)
	{
	}

	//-------------------------------------------------------------------------------------------------
	inline SceneObject::SceneObject(Ptr<Graphics::Model> model, Matrix transformation, bool solid) : Model(model), Transformation(transformation), Solid(solid)
	{
	}

	//-------------------------------------------------------------------------------------------------
	inline SceneObject::SceneObject(const String& name, Ptr<Graphics::Model> model, Matrix transformation, bool solid) : name(name), Model(model), Transformation(transformation), Solid(solid)
	{
	}
}