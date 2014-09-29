#include "Room1.h"
#include "GameObject.h"
#include "Link.h"
#include "ZeldaGame.h"

void Room1::Initialize()
{
    link = New<Link>();
    link->x = 200;
    link->y = 20;
    AddObject ( link );
    base::Initialize();
}

void Room1::LoadContent()
{
    SetBackground ( 0, ContentManager::Load<TiledBackground> ( "newGameMap2" ).get() );
    base::LoadContent();
}

