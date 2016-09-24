#include <Refactoring2DEngineTest.h>
#include "GraphicsDevice.h"
#include "BackgroundMemory.h"
#include "SpriteMemory.h"
#include "ContentManager.h"
#include "Background.h"
#include "TileSet.h"
#include "Map.h"
#include "Sprite.h"
#include "PaletteMemory.h"
#include "ObjectAttributeMemory.h"
#include "VideoRamBank.h"

using namespace Framework;
using namespace System;
using namespace Graphics;

void Refactoring2DEngineTest::Initialize()
{
	super::Initialize();

	imageIndex = 0.0f;

	GraphicsDevice::Main.SpriteMemory->PaletteMemory->AddColor(Color::Green);
	GraphicsDevice::Main.BackgroundMemory->AutomaticExpansion = false;
	GraphicsDevice::Main.SpriteMemory->AutomaticExpansion = false;

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
	
	auto linkTiles = Content.Load<TileSet>("red32x32");
	GraphicsDevice::Main.SpriteMemory->AssignBankToSlot(BankA, 0);
	
	// Everything is fine when putting this here
	GraphicsDevice::Main.BackgroundMemory->AssignBankToSlot(BankB, 0);

	for (int i = 0; i < 16; ++i) {
		GraphicsDevice.SpriteMemory->AddTile(linkTiles->Tiles[i]);
	}

	// Sprite not drawn when putting this here
	//GraphicsDevice::Main.BackgroundMemory->AssignBankToSlot(BankB, 0);

	sprite = Sprite();
	sprite.Priority = OBJPRIORITY_0;
	sprite.ImageIndex = 0;
	sprite.ImageSpeed = 1;
	sprite.size = OBJSIZE_32;
	sprite.shape = OBJSHAPE_SQUARE;
	sprite.Identifier = linkTiles->Tiles[0].Identifier;

	auto tileSet = Content.Load<TileSet>("background");

	// TODO: Drawing only the background is working, drawing only 1 sprite is kinda working, when both are drawn,
	// the sprite does not even appear in sprite memory

	auto &map = GraphicsDevice::Main.BackgroundMemory->Maps[0];

	for (int i = 0; i < tileSet->GetTileCount8x8(); ++i) {
		auto &tile = tileSet->Tiles[i];
		auto vramIndex = GraphicsDevice::Main.BackgroundMemory->AddTile(tile);
		map->SetTile(i, ScreenBlockEntry(vramIndex));
	}

	sassert(GraphicsDevice::Main.BackgroundMemory->GetMappedBanks()[0]->GetName() == BankB, "Nooo");
	sassert(GraphicsDevice::Main.SpriteMemory->GetMappedBanks()[0]->GetName() == BankA, "Nooo2");
	sassert(GraphicsDevice::Main.BackgroundMemory->GetMappedBanks()[0]->GetOwner()->GetIndex() == 0, "Nooo3");
	sassert(GraphicsDevice::Main.SpriteMemory->GetMappedBanks()[0]->GetOwner()->GetIndex() == 0, "Nooo4");
}

void Refactoring2DEngineTest::Update(const GameTime &gameTime)
{
	super::Update(gameTime);

	//imageIndex += 1.0f / 60.0f;
}

void Refactoring2DEngineTest::Draw(const GameTime &gameTime)
{
	super::Draw(gameTime);

	GraphicsDevice::Main.Backgrounds[0]->ColorMode = ColorMode::ColorMode256;
	GraphicsDevice::Main.Backgrounds[0]->ShowMapWithIndex(0);
	
	GraphicsDevice::Main.ObjectAttributeMemory.DrawSprite(sprite, 50.0f, 50.0f, 0, 1.0f, 1.0f);
}
