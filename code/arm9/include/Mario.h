#pragma once

#include "SceneObject.h"
#include "Vec3.h"
#include "types.h"

namespace Test
{
	class Test3D;

	class Mario : public Graphics::SceneObject
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

		Vector3 HandleCollisions(fx12 timeStep);

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
		Ptr<Scene> scene;

		bool CollisionsEnabled;
	};

	//-------------------------------------------------------------------------------------------------
	inline Mario::Mario() : SceneObject("mario"), CollisionsEnabled(true)
	{

	}
}