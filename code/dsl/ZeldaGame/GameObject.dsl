GameObject : DrawableGameComponent
{
	fx12 x;
	fx12 y;
	fx12 ImageSpeed = 10;
	fx12 ImageIndex;
	Sprite CurrentSprite;
	SpriteSet Sprites;
	
	void Update()
	{
		ImageIndex = (ImageIndex + ImageSpeed * ElapsedTime.Seconds()) % (fx12)((int)CurrentSprite.SubImages.size());
	}
}