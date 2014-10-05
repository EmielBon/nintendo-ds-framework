#pragma once

#include "types.h"
#include "GraphicsDevice.h"

static inline void DrawSprite(Graphics::Sprite &sprite, fx12 x, fx12 y, fx12 subImageIndex)
{
	if (y <= 192)
		Graphics::GraphicsDevice::Main.DrawSprite(sprite, x, y, subImageIndex);
	else
		Graphics::GraphicsDevice::Sub.DrawSprite(sprite, x, y - (192 + 64), subImageIndex);
}