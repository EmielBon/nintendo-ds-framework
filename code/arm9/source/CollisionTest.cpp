#include "CollisionTest.h"

// Stable libraries
#include "Input.h"
#include "Framework.h"

// Specific libraries
#include "Background.h"
#include "GraphicsDevice.h"
#include "Console.h"
#include "Model.h"
#include "Screen.h"
#include "Mat.h"
#include "MathFunctions.h"
#include "Logging.h"
#include "Vec3.h"
#include "Vertex.h"
#include "GraphicsDevice.h"

// libnds
#include <nds/arm9/videoGL.h>

namespace Test
{
	using namespace Input;
	using namespace System;
	using namespace Graphics;
	using namespace Framework;

	//-------------------------------------------------------------------------------------------------
	void CollisionTest::Initialize()
	{
		Background& bg0 = GraphicsDevice::Main.Background0;
		bg0.Enable();
		bg0.SetLayer(0);

		GraphicsDevice::Main.Enable3D(true);

		camera.Eye   = Vector3(0, 10, 10);
		camera.Focus = Vector3(0, 0, 0);
		lightDirection = Vector3(0, 1, 0);
		translation = Vector3();
		//InitializeQuad();
		dx = 0.1;
		dy = 0.1;
		super::Initialize();
	}

	//-------------------------------------------------------------------------------------------------
	void CollisionTest::LoadContent()
	{
		cube = Content.Load<Model>("icosphere");
		super::LoadContent();
	}

	//-------------------------------------------------------------------------------------------------
	void CollisionTest::Update(const GameTime &gameTime)
	{	
		KeyState   keys  = KeyPad::GetState();
	//	translation.x += dx;
		//translation.y += dy;
		if (keys.IsKeyHeld(Keys::Up))
			translation.y += 0.1f;
		else if (keys.IsKeyHeld(Keys::Down))
			translation.y -= 0.1f;
		if (keys.IsKeyHeld(Keys::Left))
			translation.x -= 0.1f;
		else if (keys.IsKeyHeld(Keys::Right))
			translation.x += 0.1f;

		if (keys.IsKeyHeld(Keys::A))
			translation.z -= 0.1f;
		else if (keys.IsKeyHeld(Keys::B))
			translation.z += 0.1f;

		worldMatrix = Matrix::CreateTranslation(translation.x, translation.y, translation.z);
		camera.UpdateViewMatrix();

		super::Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void CollisionTest::Draw(const GameTime &gameTime)
	{
		//DrawQuad();
		BoundingSphere cube1 = cube->Meshes[0].BoundingSphere.Transform(Matrix::CreateTranslation(translation.x, translation.y, translation.z));
		BoundingSphere cube2 = cube->Meshes[0].BoundingSphere.Transform(Matrix::CreateTranslation(0,0,0));
		//BoundingBox wall1 = wall->Meshes[0].BoundingBox.Transform(Matrix::CreateTranslation(-10, translation.y, translation.z));
		//BoundingBox wall2 = wall->Meshes[0].BoundingBox.Transform(Matrix::CreateTranslation(10, translation.y, translation.z));
		BasicEffect& effect = *cube->Meshes[0].MeshParts[0].Effect;
		if(cube1.Intersects(cube2))
		{
			effect.DiffuseColor = Color::DeepSkyBlue;
		}
		else
			effect.DiffuseColor = Color::Gold;
		
		DrawModel(*cube, worldMatrix);
		DrawModel(*cube, Matrix::Identity());
		//DrawModel(*wall, Matrix::CreateTranslation(-10, translation.y, translation.z));
		//DrawModel(*wall, Matrix::CreateTranslation(10, translation.y, translation.z));

		super::Draw(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void CollisionTest::DrawModel( Model& model, Matrix worldMatrix )
	{
		BasicEffect& effect = *model.Meshes[0].MeshParts[0].Effect;
		effect.Projection = camera.Projection;
		effect.View = camera.View;
		effect.World = worldMatrix;
		effect.DirectionalLight0.Direction = lightDirection;
		model.Draw();
	}
}