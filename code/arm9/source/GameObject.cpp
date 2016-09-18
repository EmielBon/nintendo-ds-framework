/*#include "GameObject.h"
#include "Link.h"
#include "Room1.h"
#include "ZeldaGame.h"

void GameObject::Initialize()
{
	Position.x = 0.0f;
	Position.y = 0.0f;
    ImageSpeed = 10;
    ImageIndex = 0.0f;
	CurrentSprite = nullptr;
    Sprites = nullptr;
    base::Initialize();
}

void GameObject::Update ( const GameTime &gameTime )
{
    //ImageIndex = ( ImageIndex + ImageSpeed * gameTime.ElapsedGameTime.TotalSeconds() ) % ( fx12 ) ( ( int ) CurrentSprite->SubImages.size() );
    base::Update ( gameTime );
}

*/
