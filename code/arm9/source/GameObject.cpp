#include "GameObject.h"
#include "Link.h"
#include "Room1.h"
#include "ZeldaGame.h"
void GameObject::Initialize()
{
	x = 0.0f;
	y = 0.0f;
	ImageSpeed = 5;
	ImageIndex = 0.0f;
	CurrentSprite = New<Sprite>();
	Sprites = New<SpriteSet>();
	base::Initialize();
}
void GameObject::Update(const GameTime &gameTime)
{
	ImageIndex =(ImageIndex + ImageSpeed * gameTime.ElapsedGameTime.TotalSeconds())%(fx12 )(( int)CurrentSprite->SubImages.size());
	base::Update(gameTime);
}

