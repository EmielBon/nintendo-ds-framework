Link : GameObject
{
	void LoadContent()
	{
		Sprites = Load<SpriteSet>("link");
		CurrentSprite = Sprites["link_down"];
	}
	
	void Update()
	{
		fx12 speed = 96;
		fx12 timeStep = ElapsedTime.Seconds();
		
		Vector2 direction(0, 0);
		if (!IsKeyHeld(Keys.All))
		{
			CurrentSprite.SubImageIndex = 0;
		}
		if (IsKeyHeld(Keys.Left) ) 
		{
			direction.x = -1;
			CurrentSprite = Sprites["link_left"];
		}
		if (IsKeyHeld(Keys.Right)) 
		{
			direction.x = 1;
			CurrentSprite = Sprites["link_right"];
		}
		if (IsKeyHeld(Keys.Up)) 
		{
			direction.y = -1;
			CurrentSprite = Sprites["link_up"];
		}
		if (IsKeyHeld(Keys.Down))
		{
			direction.y = 1;
			CurrentSprite = Sprites["link_down"];
		}
		
		direction = direction.Normalize();
		x += direction.x * speed * timeStep;
		y += direction.y * speed * timeStep;
	}

	void Draw()
	{
		DrawSprite(CurrentSprite, x, y, ImageIndex);
	}
}