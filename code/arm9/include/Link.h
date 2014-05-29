#pragma once

#include "ZeldaGameTypes.h"
class Link : public GameObject 
{
	private: using base = GameObject;
public:
	void Initialize();
	void LoadContent();
	void Update(const GameTime &gameTime);
	void Draw(const GameTime &gameTime);
public:
}
;

