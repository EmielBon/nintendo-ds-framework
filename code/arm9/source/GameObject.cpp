#include "GameObject.h"
#include "Sprite.h"
#include "GraphicsDevice.h"
#include "ObjectAttributeMemory.h"

namespace Framework2D
{
	using namespace Graphics;

	void GameObject::Update(const GameTime &gameTime)
	{
		ImageIndex = (ImageIndex + ImageSpeed) % (fx12)((int)Sprite->SubImages.size());
	}

	void GameObject::DrawSprite(Ptr<Graphics::Sprite> sprite, fx12 x, fx12 y, fx12 subImageIndex)
	{
		if (y <= 192)
			GraphicsDevice::Main.ObjectAttributeMemory.DrawSprite(sprite, x, y, subImageIndex);
		else
			GraphicsDevice::Sub.ObjectAttributeMemory.DrawSprite(sprite, x, y - (192 + 64), subImageIndex);
	}
}