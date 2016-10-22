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

	// TODO: Drawing only the background is working, drawing only 1 sprite is kinda working, when both are drawn,
	// the sprite does not even appear in sprite memory
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

	auto bitmapBackground = Content.Load<Texture>("background_bitmap");
	auto address = GraphicsDevice::Main.BackgroundMemory->StartAddress();
	memcpy(address, bitmapBackground->Pixels.data(), bitmapBackground->GetByteSize());

	TiledImage linkImage = linkTiles->GetTiledImageAtIndex(59);
	sprite = GraphicsDevice.SpriteMemory->AddSprite(linkImage);
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
	
	GraphicsDevice::Main.ObjectAttributeMemory.DrawSprite(sprite, 50.0f, 50.0f, 0, 1.0f, 1.0f, OBJPRIORITY_0);
	//GraphicsDevice::Main.ObjectAttributeMemory.DrawSprite(sprite2, 100.0f, 50.0f, 0, 1.0f, 1.0f, OBJPRIORITY_0);
}
