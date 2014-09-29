#pragma once

#include "types.h"
#include "GameObject.h"

class Rabbit : public GameObject
{
public:

	Rabbit() = default;

	void LoadContent();

	void Update(const Framework::GameTime &gameTime);

	void Draw(const Framework::GameTime &gameTime);
};