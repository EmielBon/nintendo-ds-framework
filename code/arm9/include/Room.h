#pragma once

#include "types.h"
#include "DrawableGameComponent.h"
#include "GraphicsDevice.h"

namespace Framework2D
{
	class Game2D;
	class GameObject;
	
	class Room : public Framework::DrawableGameComponent
	{
	public:

		Room();

		void Initialize();

		void LoadContent();

		void Update(const Framework::GameTime &gameTime);

		void Draw(const Framework::GameTime &gameTime);

	public:

		const String Name;
		Graphics::Background &Background0, &Background1, &Background2, &Background3;

	protected:
		
		List< Ptr<GameObject> > objects;
	};

	inline Room::Room() 
		: Background0(Graphics::GraphicsDevice::Main.Background0),
		  Background1(Graphics::GraphicsDevice::Main.Background1),
		  Background2(Graphics::GraphicsDevice::Main.Background2),
		  Background3(Graphics::GraphicsDevice::Main.Background3)
	{

	}
}