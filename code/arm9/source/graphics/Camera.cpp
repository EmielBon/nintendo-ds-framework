#include "Camera.h"
#include "MathFunctions.h"
#include "GraphicsDevice.h"
#include "MathFunctions.h"
#include "BasicEffect.h"

namespace Graphics
{
	void Camera::UpdateViewMatrix()
	{
		// Create the View Matrix
		View = Matrix::CreateLookAt(Eye, Focus, Up);
	}

	void Camera::CreateProjectionMatrix(fx12 aspectRatio)
	{
		// Todo: Far plane depth of 1000.0f is problematic, why?
		Projection = Matrix::CreatePerspectiveFieldOfView(Math::Pi / 4, aspectRatio, 1.0f, 50.0f);
	}

	void Camera::SetEffectParameters( BasicEffect &effect )
	{
		effect.View = View;
		effect.Projection = Projection;
	}

}