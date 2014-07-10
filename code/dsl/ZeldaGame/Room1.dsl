Room1 : Room
{
	Link link = Link();
	
	void Initialize()
	{
		link.x = 200;
		link.y = 20;	
		AddObject(link);
	}
	
	void LoadContent()
	{
		SetBackground(0, Load<TiledBackground>("newGameMap2"));
	}
}

TiledBackground
{	
	List<MapTile>

	extern void function();
}