#include <Refactoring2DEngineTest.h>
#include "GraphicsDevice.h"
#include "Background.h"
#include "ContentManager.h"
#include "TileSet256.h"
#include "Palette.h"
#include "Map.h"
#include "BackgroundMemory.h"
#include "Sprite.h"
#include "SpriteMemory.h"
#include "PaletteMemory.h"

using namespace Framework;
using namespace System;
using namespace Graphics;

void Refactoring2DEngineTest::Initialize()
{
	imageIndex = 0.0f;

	GraphicsDevice::Sub.Backgrounds[0]->ColorMode = ColorMode16;

	console = new Console(GraphicsDevice::Sub.Backgrounds[0]);
	AddComponent(console);
	for (int i = 0; i < 64; ++i)
		console->WriteLine(ToStr("Hoi " << i));

	auto tileSet = Content.Load<TileSet256>("background");
	// Set the palette to non-transparent. Since every tile in a tileset retains a pointer to their common palette, it only has to be changed for a single tile.
	tileSet->Tiles[0].Palettes[0]->Transparent = false;

	auto &map = GraphicsDevice.BackgroundMemory->Maps[0];

	for(int i = 0; i < tileSet->GetTileCount8x8(); ++i)
	{
		auto &tile = tileSet->Tiles[i];
		GraphicsDevice.BackgroundMemory->AddTile(tile);
		map->SetTile(i, ScreenBlockEntry(tile.Identifier));
	}

	spriteSet = ContentManager::Load<SpriteSet>("link");
	sprite = spriteSet->at("link_down");
	GraphicsDevice::Main.SpriteMemory->PaletteMemory->SetTransparentColor(Color::HotPink);

	console->WriteLine("");
	super::Initialize();
}

void Refactoring2DEngineTest::LoadContent()
{
	super::LoadContent();
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
