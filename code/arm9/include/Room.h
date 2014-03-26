#pragma once

#include "types.h"
#include "DrawableGameComponent.h"

namespace Framework2D
{
	class Game2D;
	class GameObject;
	
	class Room : public Framework::DrawableGameComponent
	{
	public:

		Room(const String &name, Game2D &game);

	public:

		void Initialize();

		void LoadContent();

		void Update(const Framework::GameTime &gameTime);

		void Draw(const Framework::GameTime &gameTime);

	public:

		template<class T>
		Ptr<T> AddGameObject(int x, int y); 

	public:

		const String Name;
		Framework2D::Game2D &Game;
		Ptr<Graphics::TiledBackground> Map;

	private:
		
		List< Ptr<GameObject> > objects;
	};

	//-------------------------------------------------------------------------------------------------
	template<class T>
	inline Ptr<T> Room::AddGameObject(int x, int y)
	{
		Ptr<T> object = New<T>(Game);
		object->X = x;
		object->Y = y;
		objects.push_back(object);

		return object;
	}

}