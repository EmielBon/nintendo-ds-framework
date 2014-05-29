ZeldaGame : Game
{
	Room currentRoom;
	
	void Initialize()
	{
		currentRoom = Room1();
		Components.Add(currentRoom);
	}
}