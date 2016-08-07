#pragma once

#include "game/DrawableGameComponent.h"
#include "core/types.h"
#include "game/SceneObject.h"
#include "graphics/Light.h"

namespace Framework3D
{
	class Scene : public DrawableGameComponent
	{
	public:

		Scene() { };

		void Initialize();

		void LoadContent();

		void Update(const GameTime &gameTime);

		void Draw(const GameTime &gameTime);

		void AddObject(Ptr<SceneObject> object);

		void AddObject(Ptr<Model> model, Matrix transformation);

		Ptr<SceneObject> GetObject(const String &name) const;

		bool PlaceFree(Ptr<Model> model, const Matrix &transformation);

		Ptr<BoundingBox> PlaceFree(Ptr<Model> model, const Matrix &transformation, const Vector3 &speed);

	private:

		void DrawModel(Model &model, const Matrix &worldMatrix);

		void DrawBoundingBoxes(Model &model, const Matrix &worldMatrix);

		void DrawBoundingSpheres(Model &model, const Matrix &worldMatrix);

	public:

		List< Ptr<SceneObject> > Objects;
		List<Light> Lights;
		Color Ambient;
		Ptr<Graphics::Camera> Camera;
		bool BoundingBoxesVisible;
	};

	//-------------------------------------------------------------------------------------------------
	inline void Scene::AddObject(Ptr<SceneObject> object)
	{
		Objects.push_back(object);
		object->Initialize();
	}

	//-------------------------------------------------------------------------------------------------
	inline void Scene::AddObject( Ptr<Model> model, Matrix transformation)
	{
		AddObject( New<SceneObject>(model, transformation) );
	}
}