#include "FlyingCamera.h"
#include "MathFunctions.h"
#include "Input.h"
#include "GameTime.h"
#include "Logging.h"
#include "Vec2.h"
namespace Graphics
{
	using namespace Input;

	//-------------------------------------------------------------------------------------------------
	FlyingCamera::FlyingCamera(Vector3 eye, Vector3 focus, fx12 aspectRatio) : super(eye, focus, aspectRatio)
	{
		// Todo: Mostly untested for eyes other than starting
		/*Vector3 v1 = Vector3(Eye.x - Focus.x, 0, Eye.z - Focus.z);
		Vector3 v2 = Vector3(0, 0, 1);
		fx12 product = Vector3::Dot(v1, v2) / (v1.Length() * v2.Length());
		
		Yaw = Math::Acos((float)product) + Math::Pi;	
		Vector3 v3 = Vector3(0, v1.y, 0);
		Pitch = Math::Acos((float)(Vector3::Dot(v1, v3) / (v2.Length() * v3.Length()))) - Math::Pi/2;*/
		Vector3 lookAt = LookAt();
		lookAt.y = 0;
		lookAt = lookAt.Normalize();
		Yaw =  Math::Acos(Vector3::Dot(lookAt, Vector3::UnitX())) * -Math::Sign(lookAt.z);
		//ASSERT2(false, lookAt.ToString());

		lookAt = LookAt();
		lookAt = Vector3::Transform(lookAt, Matrix::CreateRotationY(-Yaw).M);
		lookAt.x = 0;
		lookAt = lookAt.Normalize();
		Pitch = Math::Acos(Vector3::Dot(lookAt, Vector3::UnitZ())) * -Math::Sign(lookAt.y);
	}

	//-------------------------------------------------------------------------------------------------
	void FlyingCamera::Initialize()
	{

	}

	//-------------------------------------------------------------------------------------------------
	void FlyingCamera::UpdateViewMatrix()
	{
		Matrix rotation = Matrix::CreateRotationX(Pitch) * Matrix::CreateRotationY(Yaw);

		// Move the Eye vector, determine the movement relative to the camera
		Eye += Vector3::Transform(moveVector, rotation.M);
		// Reset the move vector
		moveVector = Vector3();
		
		// Rotate the focus vector
		Vector3 forward(0, 0, -1);
		Vector3 cameraForward = Vector3::Transform(forward, rotation.M);
		Focus = Eye + cameraForward;

		// Rotate the up vector
		Vector3 cameraUp = Vector3::Transform(Up, rotation.M);

		// Create the View Matrix
		View = Matrix::CreateLookAt(Eye, Focus, cameraUp);
	}

	//-------------------------------------------------------------------------------------------------
	void FlyingCamera::Rotate(float yaw, float pitch, float roll)
	{
		Yaw += yaw;
		Pitch += pitch;
	}

	//-------------------------------------------------------------------------------------------------
	void FlyingCamera::Update(const GameTime &gameTime)
	{
		static TouchState oldState;

		KeyState   keys  = KeyPad::GetState();
		TouchState touch = TouchScreen::GetState();

		// Difference in movement
		float dx = 0;
		float dy = 0;
		// Difference in view
		float dx2 = 0;
		float dy2 = 0;

		//float dAngleY = 0;
		float speed = 10;
		float dScale = 1.0f;
		// Todo: calculate from GameTime
		float timeStep = gameTime.ElapsedGameTime.TotalSeconds();

		if (keys.IsKeyHeld(Keys::Up))
			dy = speed * timeStep;
		else if (keys.IsKeyHeld(Keys::Down))
			dy = -speed * timeStep;
		if (keys.IsKeyHeld(Keys::Left))
			dx = speed * timeStep;
		else if (keys.IsKeyHeld(Keys::Right))
			dx = -speed * timeStep;

		if (keys.IsKeyHeld(Keys::A))
			dScale -= timeStep;
		else if (keys.IsKeyHeld(Keys::B))
			dScale += timeStep;

		if (keys.IsKeyPressed(Keys::Touch))
			oldState = touch;
		if (keys.IsKeyHeld(Keys::Touch))
		{
			dx2 = ((float)touch.Position.px - oldState.Position.px) / 2 * timeStep;
			dy2 = ((float)touch.Position.py - oldState.Position.py) / 2 * timeStep;
			oldState = touch;
		}

		Move(dx, 0, dy);
		Rotate(dx2, dy2, 0);

		super::Update(gameTime);
	}

}