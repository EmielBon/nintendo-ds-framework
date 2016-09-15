#include <Refactoring2DEngineTest.h>
#include "GraphicsDevice.h"
#include "BackgroundMemory.h"
#include "SpriteMemory.h"
#include "ContentManager.h"
#include "Background.h"
#include "TileSet.h"
#include "Map.h"
#include "Sprite.h"

using namespace Framework;
using namespace System;
using namespace Graphics;

void Refactoring2DEngineTest::Initialize()
{
	super::Initialize();

	imageIndex = 0.0f;

	//GraphicsDevice::Sub.Backgrounds[0]->ColorMode = ColorMode16;
	//GraphicsDevice::Main.SpriteMemory->PaletteMemory->SetTransparentColor(Color::HotPink);

	//console = new Console(GraphicsDevice::Sub.Backgrounds[0]);
	//AddComponent(console);

//	for (int i = 0; i < 64; ++i) {
//		console->WriteLine(ToStr("Hoi " << i));
//	}
//
//	console->WriteLine("");

}

void Refactoring2DEngineTest::LoadContent()
{
	super::LoadContent();

	auto tileSet = Content.Load<TileSet>("background");

	auto &map = GraphicsDevice.BackgroundMemory->Maps[0];

	for (int i = 0; i < tileSet->GetTileCount8x8(); ++i) {
		auto &tile = tileSet->Tiles[i];
		GraphicsDevice.BackgroundMemory->AddTile(tile);
		map->SetTile(i, ScreenBlockEntry(tile.Identifier));
	}

	spriteSet = ContentManager::Load<SpriteSet>("link");
	sprite = spriteSet->at("link_down");
}

void Refactoring2DEngineTest::Update(const GameTime &gameTime)
{
	super::Update(gameTime);

	imageIndex += 1.0f / 60.0f;
}

void Refactoring2DEngineTest::Draw(const GameTime &gameTime)
{
	super::Draw(gameTime);

	GraphicsDevice::Main.Backgrounds[0]->ColorMode = ColorMode::ColorMode256;
	GraphicsDevice::Main.Backgrounds[0]->ShowMapWithIndex(0);

	GraphicsDevice::Main.DrawSprite(*sprite, 50.0f, 50.0f, imageIndex, 1.0f, 1.0f);
}
