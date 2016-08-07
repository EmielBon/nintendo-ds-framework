#include "apps/Link.h"
#include "game/GameObject.h"
#include "apps/Room1.h"
#include "apps/ZeldaGame.h"
#include "graphics/SpriteMemory.h"
#include "graphics/PaletteMemory.h"

void Link::Initialize()
{
    base::Initialize();
}

void Link::LoadContent()
{
    Sprites = ContentManager::Load<SpriteSet>("link").get();
	CurrentSprite = Sprites->at("link_down");
	GraphicsDevice::Main.SpriteMemory->PaletteMemory->SetTransparentColor(Color::HotPink);
    base::LoadContent();
}

void Link::Update ( const GameTime &gameTime )
{
    fx12 speed = 96;
    fx12 timeStep = gameTime.ElapsedGameTime.TotalSeconds();
    Vector2 direction ( 0, 0 );

    if ( !KeyPad::GetState().IsKeyHeld ( Keys::All ) )
    {
        ImageIndex = 0;
    }

    if ( KeyPad::GetState().IsKeyHeld ( Keys::Left ) )
    {
        direction.x = -1;
        CurrentSprite = Sprites->at ( "link_left" );
    }

    if ( KeyPad::GetState().IsKeyHeld ( Keys::Right ) )
    {
        direction.x = 1;
		CurrentSprite = Sprites->at("link_right");
    }

    if ( KeyPad::GetState().IsKeyHeld ( Keys::Up ) )
    {
        direction.y = -1;
		CurrentSprite = Sprites->at("link_up");
    }

    if ( KeyPad::GetState().IsKeyHeld ( Keys::Down ) )
    {
        direction.y = 1;
		CurrentSprite = Sprites->at("link_down");
    }

    direction = direction.Normalize();
	Position.x += direction.x * speed * timeStep;
	Position.y += direction.y * speed * timeStep;
    base::Update ( gameTime );
}

void Link::Draw ( const GameTime &gameTime )
{
	DrawSprite(*CurrentSprite, Position.x, Position.y, ImageIndex);
    base::Draw ( gameTime );
}

