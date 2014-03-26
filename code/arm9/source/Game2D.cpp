#include "Game2D.h"
#include "Room.h"
#include "Logging.h"

namespace Framework2D
{
	using namespace Graphics;

	//-------------------------------------------------------------------------------------------------
	void Game2D::GoToRoom(const String &name)
	{
		auto room = rooms.find(name);

		if (room == rooms.end())
		{
			LOG_WARNING("Specified room doesn't exist");
			return;
		}
		
		if (currentRoom != nullptr)
			Components.Remove(currentRoom);
		currentRoom = room->second;
		// Todo: Find a way to fix this
		currentRoom->Initialize();
		currentRoom->LoadContent();
		Components.Add(currentRoom);
	}

	//-------------------------------------------------------------------------------------------------
	Ptr<Room> Game2D::CreateRoom(const String &name)
	{
		auto result = rooms.find(name);

		if (result != rooms.end())
		{
			LOG_WARNING("Attempt to create room with existing name");
			return result->second;
		}

		Ptr<Room> room = New<Room>(name, *this);
		rooms[name] = room;
		return room;
	}

	//-------------------------------------------------------------------------------------------------
	Ptr<Room> Game2D::GetRoom(const String &name)
	{
		auto room = rooms.find(name);

		if (room != rooms.end())
			return room->second;

		return nullptr;
	}
}