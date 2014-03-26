#pragma once

#include "Game.h"
#include "types.h"

namespace Framework2D
{
	class Game2D : public Framework::Game
	{
	private:

		using super = Framework::Game;

	protected:

		/// 
		Game2D() { };

	public:

		/// 
		void GoToRoom(const String &roomName);

		/// 
		Ptr<Room> CreateRoom(const String &name);

		/// 
		Ptr<Room> GetRoom(const String &name);

		/// 
		Room& CurrentRoom();

	private:

		Ptr<Room> currentRoom;
		TreeMap< String, Ptr<Room> > rooms;
	};

	//-------------------------------------------------------------------------------------------------
	inline Room& Game2D::CurrentRoom()
	{
		return *currentRoom;
	}
}