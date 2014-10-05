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

	void DidCollideWithObject(const Framework::BoundingBox &bbox);

public:

	fx8 scale;
	Vector2 speed;
	fx12 gravity;
	Framework::BoundingBox BoundingBox;
};