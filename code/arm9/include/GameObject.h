#pragma once

#include "ZeldaGameTypes.h"
class GameObject : public DrawableGameComponent 
{
	private: using base = DrawableGameComponent;
public:
	void Initialize();
	void Update(const GameTime &gameTime);
public:
	fx12 x;
	fx12 y;
	fx12 ImageSpeed;
	fx12 ImageIndex;
	Ptr<Sprite> CurrentSprite;
	Ptr<SpriteSet> Sprites;
}
;

