#include "ZeldaGame.h"
#include "GameObject.h"
#include "Link.h"
#include "Room.h"
#include "Room1.h"

void ZeldaGame::Initialize()
{
    currentRoom = new Room1();
    Components.Add ( currentRoom );
    base::Initialize();
}

