#pragma once

#include "ZeldaGameTypes.h"

class GameObject : public DrawableGameComponent
{
private:
    using base = DrawableGameComponent;
public:
    void Initialize();
    void Update ( const GameTime &gameTime );
public:
    
	Vector2 Position;
    fx12 ImageSpeed;
    fx12 ImageIndex;
    Sprite *CurrentSprite;
    SpriteSet *Sprites;
};