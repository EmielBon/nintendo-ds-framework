#include "apps/Room1.h"
#include "game/GameObject.h"
#include "apps/Link.h"
#include "apps/ZeldaGame.h"

void Room1::Initialize()
{
    link = New<Link>();
	link->Position.x = 200;
	link->Position.y = 20;
    AddObject ( link );
    base::Initialize();
}

void Room1::LoadContent()
{
    SetBackground ( 0, ContentManager::Load<TiledBackground> ( "newGameMap2" ).get() );
    base::LoadContent();
}

