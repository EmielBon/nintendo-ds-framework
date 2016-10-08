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
#include "Texture.h"

using namespace Framework;
using namespace System;
using namespace Graphics;

void Refactoring2DEngineTest::Initialize()
{

	imageIndex = 0.0f;

	GraphicsDevice::Main.SetMode(5);

	GraphicsDevice::Main.Backgrounds[0]->Disable();
	GraphicsDevice::Main.Backgrounds[2]->Enable();
	GraphicsDevice::Sub.Backgrounds[0]->Enable();

	GraphicsDevice::Main.Backgrounds[0]->ColorMode = ColorMode::ColorMode256;
	GraphicsDevice::Main.Backgrounds[2]->ColorMode = ColorMode::ColorMode256;
	GraphicsDevice::Sub.Backgrounds[0]->ColorMode = ColorMode::ColorMode256;

	GraphicsDevice::Main.SpriteMemory->AssignBankToSlot(BankA, 0);
	GraphicsDevice::Main.BackgroundMemory->AssignBankToSlot(BankB, 0);
	GraphicsDevice::Sub.BackgroundMemory->AssignBankToSlot(BankC, 0);

	GraphicsDevice::Main.Backgrounds[2]->SetType(BackgroundType::TrueColorBitmap256x256);

	//GraphicsDevice::Main.SpriteMemory->PaletteMemory->SetTransparentColor(Color::HotPink);

	console = new Console(GraphicsDevice::Sub.Backgrounds[0]);
	AddComponent(console);

	console->WriteLine(ToStr("abcdefghijklmnopqrstuvwxyz "));

	console->WriteLine("");

	super::Initialize();
}

void Refactoring2DEngineTest::LoadContent()
{
	super::LoadContent();
	
	auto tileSet = Content.Load<TileSet>("background");

	auto linkTiles = Content.Load<TileSet>("link32x32");
	auto rabbitTiles = Content.Load<TileSet>("rabbit16x16");

	/*auto &map = GraphicsDevice::Main.BackgroundMemory->Maps[0];

	for (int i = 0; i < tileSet->GetTileCount8x8(); ++i) {
		auto &tile = tileSet->Tiles[i];
		auto vramIndex = GraphicsDevice::Main.BackgroundMemory->AddTile(tile);
		map->SetTile(i, ScreenBlockEntry(vramIndex));
	}*/

	auto bitmapBackground = Content.Load<Texture>("background_bitmap");
	auto address = GraphicsDevice::Main.BackgroundMemory->StartAddress();
	memcpy(address, bitmapBackground->Pixels.data(), bitmapBackground->GetByteSize());

	for (int i = 0; i < 16; ++i) {
		GraphicsDevice.SpriteMemory->AddTile(linkTiles->Tiles[i]);
	}

	for (int i = 0; i < 4; ++i) {
		GraphicsDevice.SpriteMemory->AddTile(rabbitTiles->Tiles[i]);
	}
	
	sprite = Sprite();
	sprite.Priority = OBJPRIORITY_0;
	sprite.ImageIndex = 0;
	sprite.ImageSpeed = 1;
	sprite.size = OBJSIZE_32;
	sprite.shape = OBJSHAPE_SQUARE;
	sprite.Identifier = linkTiles->Tiles[0].Identifier;
	
	sprite2 = Sprite();
	sprite2.Priority = OBJPRIORITY_0;
	sprite2.ImageIndex = 0;
	sprite2.ImageSpeed = 1;
	sprite2.size = OBJSIZE_16;
	sprite2.shape = OBJSHAPE_SQUARE;
	sprite2.Identifier = rabbitTiles->Tiles[0].Identifier;

	// TODO: Drawing only the background is working, drawing only 1 sprite is kinda working, when both are drawn,
	// the sprite does not even appear in sprite memory
	

	
	//sassert(GraphicsDevice::Main.BackgroundMemory->GetMappedBanks()[0]->GetName() == BankB, "Nooo");
	//sassert(GraphicsDevice::Main.SpriteMemory->GetMappedBanks()[0]->GetName() == BankA, "Nooo2");
	//sassert(GraphicsDevice::Main.BackgroundMemory->GetMappedBanks()[0]->GetOwner()->GetIndex() == 0, "Nooo3");
	//sassert(GraphicsDevice::Main.SpriteMemory->GetMappedBanks()[0]->GetOwner()->GetIndex() == 0, "Nooo4");
}

void Refactoring2DEngineTest::Update(const GameTime &gameTime)
{
	super::Update(gameTime);

	//imageIndex += 1.0f / 60.0f;
}

void Refactoring2DEngineTest::Draw(const GameTime &gameTime)
{
	super::Draw(gameTime);

	//GraphicsDevice::Main.Backgrounds[0]->ShowMapWithIndex(0);
	//GraphicsDevice::Main.Backgrounds[2]->ShowMapWithIndex(0);

	GraphicsDevice::Sub.Backgrounds[0]->ShowMapWithIndex(0);
	
	GraphicsDevice::Main.ObjectAttributeMemory.DrawSprite(sprite, 50.0f, 50.0f, 0, 1.0f, 1.0f);
	GraphicsDevice::Main.ObjectAttributeMemory.DrawSprite(sprite2, 100.0f, 50.0f, 0, 1.0f, 1.0f);
}
