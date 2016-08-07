#include "game/Scene.h"
#include "graphics/Model.h"
#include "graphics/Camera.h"
#include "graphics/BasicEffect.h"
#include "game/DrawableGameComponent.h"
#include "system/ContentManager.h"
#include "debug/Debug.h"
#include "util/StringHelper.h"

namespace Framework3D
{
	//-------------------------------------------------------------------------------------------------
	void Scene::Initialize()
	{
		if (Camera)
			Camera->Initialize();

		BoundingBoxesVisible = false;

		for (auto &object : Objects)
		{
			object->Initialize();
		}
	}

	//-------------------------------------------------------------------------------------------------
	void Scene::LoadContent()
	{
		for (auto &object : Objects)
		{
			object->LoadContent();
		}
	}

	//-------------------------------------------------------------------------------------------------
	void Scene::Update(const GameTime &gameTime)
	{
		for (auto &object : Objects)
		{
			if (object->Enabled)
				object->Update(gameTime);
		}

		if (Camera)
			Camera->Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void Scene::Draw(const GameTime &gameTime)
	{
		PROFILE_METHOD(ScnDrw);

		for(auto &object : Objects)
		{
			if (object->Visible)
			{
				DrawModel(*object->Model, object->Transformation);
				//if (BoundingBoxesVisible && object->Solid)
				//	DrawBoundingBoxes(*object->Model, object->Transformation);
			}
		}
	}

	//-------------------------------------------------------------------------------------------------
	Ptr<SceneObject> Scene::GetObject(const String &name) const
	{
		for(auto &object : Objects)
		{
			if (object->name == name)
				return object;
		}
		return nullptr;
	}

	//-------------------------------------------------------------------------------------------------
	
	bool Scene::PlaceFree(Ptr<Model> model, const Matrix &transform)
	{
		/*PROFILE_METHOD(ScePlF);
		auto bbox1 = model->Meshes[0].BoundingBox.Transform(transform);

		for(auto it = Objects.begin(); it != Objects.end(); ++it)
		{
			auto object = *it;
			auto otherModel = object->Model;
			
			if (otherModel == model)
			{		
				continue;
			}
			if (!object->Solid)
				continue;

			auto bbox2 = otherModel->Meshes[0].BoundingBox.Transform(object->Transformation);
			if(bbox1.Contains(bbox2) != ContainmentType::Disjoint) return false;
		}*/

		return true;
	}

	Ptr<BoundingBox> Scene::PlaceFree(Ptr<Model> model, const Matrix &transform, const Vector3 &speed)
	{
		/*PROFILE_METHOD(ScePf2);
		auto bbox = model->Meshes[0].BoundingBox.Transform(transform);

		Ptr<BoundingBox> newBboxX = New<BoundingBox>(bbox.Min, bbox.Max);
		newBboxX->Min.x += speed.x;
		newBboxX->Max.x += speed.x;
		
		Ptr<BoundingBox> newBboxY = New<BoundingBox>(bbox.Min, bbox.Max);
		newBboxY->Min.y += speed.y;
		newBboxY->Max.y += speed.y;

		Ptr<BoundingBox> newBboxZ = New<BoundingBox>(bbox.Min, bbox.Max);
		newBboxZ->Min.z += speed.z;
		newBboxZ->Max.z += speed.z;
		
		for(auto it = Objects.begin(); it != Objects.end(); ++it)
		{
			auto object = *it;
			auto other = object->Model;

			if(other == model) continue;
			if(!object->Solid) continue;

			Ptr<BoundingBox> bbox2 = New<BoundingBox>(other->Meshes[0].BoundingBox.Transform(object->Transformation));
			if(newBboxX->Contains(*bbox2) != ContainmentType::Disjoint) return bbox2;
			if(newBboxY->Contains(*bbox2) != ContainmentType::Disjoint) return bbox2;
			if(newBboxZ->Contains(*bbox2) != ContainmentType::Disjoint) return bbox2;
		}*/
		return nullptr;
	}

	//-------------------------------------------------------------------------------------------------
	void Scene::DrawModel(Model& model, const Matrix &worldMatrix)
	{
		for(auto &mesh : model.Meshes)
		{
			BasicEffect& effect = *mesh.MeshParts[0].Effect;
			Camera->SetEffectParameters(effect);
			effect.World = worldMatrix;
			effect.LightingEnabled = true;
			effect.DirectionalLight0.Enabled = true;
			effect.DirectionalLight0.Direction = Lights[0].Direction;
			effect.AmbientLightColor = Color::Gray;
			mesh.Draw();
		}
	}

	//-------------------------------------------------------------------------------------------------
	void Scene::DrawBoundingBoxes(Model &model, const Matrix &worldMatrix)
	{
		/*static Ptr<Model> cube = ContentManager::Load<Model>("cube");

		auto bbox = model.Meshes[0].BoundingBox.Transform(worldMatrix);
		
		DrawModel(*cube, Matrix::CreateScale(bbox.Max - bbox.Min) * Matrix::CreateTranslation((bbox.Min + bbox.Max) * 0.5f));*/
	}

	//-------------------------------------------------------------------------------------------------
	void Scene::DrawBoundingSpheres(Model &model, const Matrix &worldMatrix)
	{
		/*static Ptr<Model> sphere = ContentManager::Load<Model>("sphere");

		auto bSphere = model.Meshes[0].BoundingSphere.Transform(worldMatrix);
		auto &pos    = bSphere.Center;
		fx12 radius = bSphere.Radius;
		// Todo: Goes wrong
		DrawModel(*sphere, Matrix::CreateScale(radius * 2) * Matrix::CreateTranslation(pos.x, pos.y, pos.z));*/
	}

}