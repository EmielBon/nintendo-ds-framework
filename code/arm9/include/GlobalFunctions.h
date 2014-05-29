#pragma once

#include "types.h"
#include "GraphicsDevice.h"

static inline void DrawSprite(Ptr<Graphics::Sprite> sprite, fx12 x, fx12 y, fx12 subImageIndex)
{
	if (y <= 192)
		Graphics::GraphicsDevice::Main.ObjectAttributeMemory.DrawSprite(sprite, x, y, subImageIndex);
	else
		Graphics::GraphicsDevice::Sub.ObjectAttributeMemory.DrawSprite(sprite, x, y - (192 + 64), subImageIndex);
}