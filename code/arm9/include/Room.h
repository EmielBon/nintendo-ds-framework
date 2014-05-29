#pragma once

#include "types.h"
#include "DrawableGameComponent.h"

class GameObject;

namespace Framework2D
{
	class Game2D;
	
	class Room : public Framework::DrawableGameComponent
	{
	public:

		Room();

		void Initialize();

		void LoadContent();

		void Update(const Framework::GameTime &gameTime);

		void Draw(const Framework::GameTime &gameTime);

		void AddObject(Ptr<GameObject> obj);

		void SetBackground(int index, Ptr<Graphics::TiledBackground> background);

	public:

		const String Name;
		Graphics::Background &Background0, &Background1, &Background2, &Background3;

	protected:
		
		List< Ptr<GameObject> > objects;
	};
}