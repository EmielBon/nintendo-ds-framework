#pragma once

#include "core/types.h"
#include "GameObject.h"

class Rabbit : public GameObject
{
private:
	using base = GameObject;

public:

	Rabbit() = default;

	void Initialize();

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