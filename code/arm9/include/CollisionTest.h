#pragma once

#include "Game.h"
#include "types.h"
#include "BasicEffect.h"
#include "FlyingCamera.h"
#include "Mat.h"
#include "Vertex.h"

namespace Test
{
	class CollisionTest : public Framework::Game
	{
	private:

		using super = Framework::Game;

	protected:

		void Initialize();
		void LoadContent();
		void Update(const GameTime &gameTime);
		void Draw(const GameTime &gameTime);

	protected:

		void InitializeQuad();
		void DrawQuad();
		void DrawModel(Graphics::Model& model, Framework::Matrix worldMatrix);

	protected:

		Graphics::FlyingCamera camera;
		Ptr<Graphics::Model> cube;
		Ptr<Graphics::Model> wall;
		List<Graphics::Vertex> quadVertices;
		List<u16> quadIndices;
		Framework::Vector3 lightDirection;
		Framework::Matrix worldMatrix;
		Framework::Matrix worldMatrix2;
		Framework::Vector3 translation;
		float dx, dy;
	};
}