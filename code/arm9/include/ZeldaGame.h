#pragma once

#include "ZeldaGameTypes.h"

class ZeldaGame : public Game
{
private:
    using base = Game;
public:
    void Initialize();
public:
    Room *currentRoom;
};