#pragma once

#include "core/types.h"
#include "game/Scene.h"
#include "game/DrawableGameComponent.h"

namespace Framework3D
{
	class GameObject;

	class Room : public Framework::DrawableGameComponent
	{
	public:

		Room(const String &name, Framework::Game &game);

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
		Framework::Game &Game;
		Graphics::Scene Scene;
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