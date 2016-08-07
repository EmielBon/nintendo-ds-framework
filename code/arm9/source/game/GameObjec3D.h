#pragma once

#include "DrawableGameComponent.h"
#include "core/types.h"

namespace Framework3D
{
	class GameObject3D : public Framework::DrawableGameComponent
	{
	protected:

		GameObject3D(Framework::Game &game);

	public:

		float X, Y, Z;
		Ptr<Graphics::Model> Model;

	protected:

		Framework::Game &Game;
	};

	//-------------------------------------------------------------------------------------------------
	inline GameObject3D::GameObject3D(Framework::Game &game) : X(0), Y(0), Z(0), Game(game)
	{

	}
}