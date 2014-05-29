#include "Link.h"
#include "GameObject.h"
#include "Room1.h"
#include "ZeldaGame.h"
void Link::Initialize()
{
	base::Initialize();
}
void Link::LoadContent()
{
	Sprites = ContentManager::Load<SpriteSet>("link");
	CurrentSprite = Sprites->at("link_down");
	base::LoadContent();
}
void Link::Update(const GameTime &gameTime)
{
	fx12 speed = 96;
	fx12 timeStep = gameTime.ElapsedGameTime.TotalSeconds();
	Vector2 direction(0, 0);
	if(!KeyPad::GetState().IsKeyHeld(Keys::All)) 
	{
		CurrentSprite->SubImageIndex = 0;
	}
	if(KeyPad::GetState().IsKeyHeld(Keys::Left)) 
	{
		direction.x = -1;
		CurrentSprite = Sprites->at("link_left");
	}
	if(KeyPad::GetState().IsKeyHeld(Keys::Right)) 
	{
		direction.x = 1;
		CurrentSprite = Sprites->at("link_right");
	}
	if(KeyPad::GetState().IsKeyHeld(Keys::Up)) 
	{
		direction.y = -1;
		CurrentSprite = Sprites->at("link_up");
	}
	if(KeyPad::GetState().IsKeyHeld(Keys::Down)) 
	{
		direction.y = 1;
		CurrentSprite = Sprites->at("link_down");
	}
	direction = direction.Normalize();
	x += direction.x * speed * timeStep;
	y += direction.y * speed * timeStep;
	base::Update(gameTime);
}
void Link::Draw(const GameTime &gameTime)
{
	DrawSprite(CurrentSprite, x, y, ImageIndex);
	base::Draw(gameTime);
}

