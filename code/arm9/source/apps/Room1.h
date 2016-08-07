#pragma once

#include "apps/ZeldaGameTypes.h"

class Room1 : public Room
{
private:
    using base = Room;
public:
    void Initialize();
    void LoadContent();
public:
    Ptr<Link> link;
};