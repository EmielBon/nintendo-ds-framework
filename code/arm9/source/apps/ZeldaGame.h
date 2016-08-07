#pragma once

#include "apps/ZeldaGameTypes.h"

class ZeldaGame : public Game
{
private:
    using base = Game;
public:
    void Initialize();
public:
    Room *currentRoom;
};