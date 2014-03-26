#include "Mario.h"
#include "Input.h"
#include "Texture.h"
#include "MathFunctions.h"
#include "Test3D.h"
#include "Model.h"
#include "BasicEffect.h"
#include "Debug.h" 
#include "Scene.h"
#include "SceneObject.h"

namespace Test
{
	using namespace Input;

	//-------------------------------------------------------------------------------------------------
	void Mario::Initialize()
	{
		frontFacing = true;
		scale = 1.0f;
		flip = 1;

		imageIndex = 0;
	}

	//-------------------------------------------------------------------------------------------------
	void Mario::LoadContent()
	{
		// Load the models
		Model = ContentManager::Load<Graphics::Model>("mario");
		// Initialize the effect
		effect = New<BasicEffect>();
		standFrontSprite = ContentManager::Load<Texture>("mario_standstill");
		standBackSprite  = ContentManager::Load<Texture>("mario_back_standstill");
		walkFrontSprite.push_back( ContentManager::Load<Texture>("mario_run0") );
		walkFrontSprite.push_back( ContentManager::Load<Texture>("mario_run1") );
		walkFrontSprite.push_back( ContentManager::Load<Texture>("mario_run2") );
		walkBackSprite.push_back( ContentManager::Load<Texture>("mario_back_run0") );
		walkBackSprite.push_back( ContentManager::Load<Texture>("mario_back_run1") );
		walkBackSprite.push_back( ContentManager::Load<Texture>("mario_back_run2") );
		jumpFrontSprite = ContentManager::Load<Texture>("mario_jump");
		jumpBackSprite  = ContentManager::Load<Texture>("mario_back_jump");
		effect->Texture = standFrontSprite;
		// Set the effect
		Model->Meshes[0].MeshParts[0].Effect = effect;
		Transformation = Matrix::CreateScale(1.0f * scale, -1.0f, 1.0f) * Matrix::CreateTranslation(position.x, position.z, position.y);
	}

	//-------------------------------------------------------------------------------------------------
	void Mario::Update(const GameTime &gameTime)
	{
		PROFILE_METHOD(MarUpd);
		KeyState keys = KeyPad::GetState();
		
		fx12 acceleration = 20;
		fx12 friction = 20;
		fx12 maxSpeed = 5;
		fx12 timeStep = gameTime.ElapsedGameTime.TotalSeconds();
		
		fx12 gravity = 25;

		//if(!InAir())
		//{
			if (keys.IsKeyHeld(Keys::Left))
				MoveX(-acceleration, timeStep);
			else if (keys.IsKeyHeld(Keys::Right))
				MoveX(acceleration, timeStep);
			else
			{
				speed.x -= Math::Sign(speed.x) * friction * timeStep;

				if (Math::Abs(speed.x) < friction * timeStep)
					speed.x = 0;
			}

			if (keys.IsKeyHeld(Keys::Up))
				MoveY(-acceleration, timeStep);
			else if (keys.IsKeyHeld(Keys::Down))
				MoveY( acceleration, timeStep);
			else
			{
				speed.y -= Math::Sign(speed.y) * friction * timeStep;

				if (Math::Abs(speed.y) < friction * timeStep)
					speed.y = 0;
			}
		
		if (!InAir())
		{
			if (keys.IsKeyPressed(Keys::A))
			{
				speed.z = 6;
			}
		}
		else
		{	
			speed.z -= gravity * timeStep;
		}

		if (speed.x != fx12(0))
			flip = (int)Math::Sign(speed.x);

		Vector3 walkSpeed(speed.x, speed.y, 0);
  
		if (walkSpeed.Length() > maxSpeed)
		{
			walkSpeed = walkSpeed.Normalize() * (fx12)maxSpeed;
			
			speed.x = walkSpeed.x;
			speed.y = walkSpeed.y;
		}

		Vector3 frameSpeed = speed * timeStep;

		if (CollisionsEnabled)
			frameSpeed = HandleCollisions(timeStep);
		
		position += frameSpeed;

		scale += flip * 8 * timeStep;

		if (scale == fx12(0) || scale == fx12(-0))
		{
			scale += flip * fx12(1) / 100;
		}

		if (Math::Abs(scale) >= fx12(1))
		{
			scale = flip;
		}

		if (speed.y < fx12(0))
			frontFacing = false;
		else if (speed.LengthSquared() > fx12(0))
			frontFacing = true;

		if ( InAir() )
			SetSprite(frontFacing ? jumpFrontSprite : jumpBackSprite);
		else if ( speed.LengthSquared() > fx12(0) )
			SetSprite(frontFacing ? walkFrontSprite : walkBackSprite);
		else
			SetSprite(frontFacing ? standFrontSprite : standBackSprite);

		imageIndex += speed.Length() * timeStep;
		Transformation = {
		  1*scale,        0,        0, position.x,
				0,		  1,        0, position.z,
				0,        0,        1, position.y,
				0,        0,        0,          1,
		};
		
		//Transformation = Matrix::CreateScale(3 * scale, 3, 3) * Matrix::CreateTranslation(position.x, position.z, position.y);
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 Mario::HandleCollisions(fx12 timeStep)
	{
		PROFILE_METHOD(MarCol);
		Vector3 frameSpeed = speed * timeStep;
		
		Matrix transform = {
			    1, 0, 0, position.x,
				0, 1, 0, position.z,
				0, 0, 1, position.y,
				0, 0, 0,          1,
		};

		Ptr<BoundingBox> other = scene->PlaceFree(Model, transform, Vector3(frameSpeed.x, frameSpeed.z, frameSpeed.y));

		if(other != nullptr)
		{
			const BoundingBox &bbox = Model->Meshes[0].BoundingBox.Transform(transform);
			if(bbox.Max.x + frameSpeed.x > other->Min.x && bbox.Max.x < other->Min.x) 
			{
				position.x = other->Min.x - (bbox.Max.x - bbox.Min.x) /2 - fx12(1) / fx12(100);
				frameSpeed.x = 0;
				speed.x = 0;
			}
			else if(bbox.Min.x + frameSpeed.x < other->Max.x && bbox.Min.x > other->Max.x) 
			{
				position.x = other->Max.x + (bbox.Max.x - bbox.Min.x) /2 + fx12(1) / fx12(100);
				frameSpeed.x = 0;
				speed.x = 0;
			}			// y collisions
			else if(bbox.Max.z + frameSpeed.y > other->Min.z && bbox.Max.z < other->Min.z)
			{
				position.y = other->Min.z - (bbox.Max.z - bbox.Min.z) /2 - fx12(1) / fx12(100);
				frameSpeed.y = 0;
				speed.y = 0;
			}
			else if(bbox.Min.z + frameSpeed.y < other->Max.z && bbox.Min.z > other->Max.z)
			{
				position.y = other->Max.z + (bbox.Max.z - bbox.Min.z) /2 + fx12(1) / fx12(100);;
				frameSpeed.y = 0;
				speed.y = 0;
			}			// z collisions
			else if(bbox.Max.y + frameSpeed.z > other->Min.y && bbox.Max.y < other->Min.y)
			{
				position.z = other->Min.y - (bbox.Max.y - bbox.Min.y) /2 - fx12(1) / fx12(100);
				frameSpeed.z = 0;
				speed.z = 0;
			}
			else if(bbox.Min.y + frameSpeed.z < other->Max.y && bbox.Min.y > other->Max.y)
			{
				position.z = other->Max.y  + fx12(1) / fx12(100);;
				frameSpeed.z = 0;
				speed.z = 0;
			}
		}

		return frameSpeed;
	}

	//-------------------------------------------------------------------------------------------------
	void Mario::SetSprite(Ptr<Texture> spr)
	{
		effect->Texture = spr;
	}

	//-------------------------------------------------------------------------------------------------
	void Mario::SetSprite(List<Ptr<Texture>> sprites)
	{
		int index = (int)imageIndex % sprites.size();
		ASSERT(index >= 0 && (u32)index < sprites.size(), "Error: Image index out of bounds");
		effect->Texture = sprites[index];
	}

	//-------------------------------------------------------------------------------------------------
	void Mario::MoveX(fx12 acceleration, fx12 timeStep)
	{
		// Stop-and-turn
		if (Math::Sign(speed.x) != Math::Sign(acceleration))
			speed.x = 0;
		speed.x += acceleration * timeStep;
	}

	//-------------------------------------------------------------------------------------------------
	void Mario::MoveY(fx12 acceleration, fx12 timeStep)
	{
		// Stop-and-turn
		if (Math::Sign(speed.y) != Math::Sign(acceleration))
			speed.y = 0;
		speed.y += acceleration * timeStep;
	}

	//-------------------------------------------------------------------------------------------------
	bool Mario::InAir()
	{
		return speed.z != fx12(0) || scene->PlaceFree(Model, Matrix::CreateScale(3, 3, 3) * Matrix::CreateTranslation(position.x , position.z - fx12(5) / fx12(100), position.y));
	}
}