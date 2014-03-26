#include "SpriteTest.h"
#include "TileSet256.h"
#include "SpriteSubImage.h"
#include "TilesManager.h"
#include "Sprite.h"

namespace Test
{
	using namespace Graphics;

	//-------------------------------------------------------------------------------------------------
	void SpriteTest::Initialize()
	{
		Background& bg0 = GraphicsDevice::Main.Background0;
		bg0.Enable();
		bg0.SetLayer(3);
		
		GraphicsDevice::Sub.SetBackgroundColor(Color::BlueViolet);

		super::Initialize();
	}

	//-------------------------------------------------------------------------------------------------
	void SpriteTest::LoadContent()
	{
		Ptr<TileSet256> tileSet = Content.Load<TileSet256>("enemy_chicken32x32");
		tileSet->SetPalette( Content.Load<Palette>("enemy_chicken32x32_pal") );

		SpriteSubImage img(4, 4);
		u32 baseId = TilesManager::IdentifierForTile(tileSet, 0);
		
		for(int j = 0; j < 4; ++j)
		for(int i = 0; i < 4; ++i)
		{
			img.TileIdentifiers[0] = baseId + i + j * 4;
		}
		
		auto subImages = List<SpriteSubImage>();
		subImages.push_back(img);

		sprite = New<Sprite>(subImages);

		super::LoadContent();
	}

	//-------------------------------------------------------------------------------------------------
	void SpriteTest::Update(const GameTime &gameTime)
	{	
		super::Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void SpriteTest::Draw(const GameTime &gameTime)
	{
		GraphicsDevice.ObjectAttributeMemory.DrawSprite(sprite);

		super::Draw(gameTime);
	}
}