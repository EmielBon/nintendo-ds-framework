#pragma once

#include "game/SceneObject.h"
#include "util/Vec3.h"
#include "core/types.h"

namespace Test
{
	class Mario : public Framework3D::SceneObject
	{
	public:

		Mario();

		void Initialize();

		void LoadContent();

		void Update(const GameTime &gameTime);

		void SetSprite(Ptr<Texture> spr);

		void SetSprite(const List<Ptr<Texture>> sprites);

		bool InAir();

		void MoveX(fx12 acceleration, fx12 timeStep);

		void MoveY(fx12 acceleration, fx12 timeStep);

		//Vector3 HandleCollisions(fx12 timeStep);

		void DidCollideWithObject(const Framework::BoundingBox &bbox);

	public:

		Vector3 position;
		Vector3 speed;

		bool frontFacing;
		fx12 scale;
		int flip;
		bool inAir;

		fx12 imageIndex;
		fx12 imageSpeed;

		Ptr<BasicEffect> effect;
		Ptr<Texture> standFrontSprite;
		Ptr<Texture> standBackSprite;
		List<Ptr<Texture>> walkFrontSprite;
		List<Ptr<Texture>> walkBackSprite;
		Ptr<Texture> jumpFrontSprite;
		Ptr<Texture> jumpBackSprite;
		Ptr<Framework3D::Scene> scene;

		bool CollisionsEnabled;

		bool initialized;
	};

	//-------------------------------------------------------------------------------------------------
	inline Mario::Mario() : SceneObject("mario"), CollisionsEnabled(true), initialized(false)
	{

	}
}