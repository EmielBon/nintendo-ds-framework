#pragma once

#include "core/types.h"
#include "game/DrawableGameComponent.h"

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

		void SetBackground(int index, Graphics::TiledBackground *background);

	public:

		const String Name;
		
	protected:
		
		List< Ptr<GameObject> > objects;
	};
}