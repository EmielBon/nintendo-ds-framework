#include "apps/ZeldaGame.h"
#include "game/GameObject.h"
#include "apps/Link.h"
#include "game/Room.h"
#include "apps/Room1.h"

void ZeldaGame::Initialize()
{
    currentRoom = new Room1();
    AddComponent ( currentRoom );
    base::Initialize();
}

