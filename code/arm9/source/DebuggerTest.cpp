#include "DebuggerTest.h"
#include "GraphicsDevice.h"
#include "Background.h"

using namespace Framework;
using namespace System;
using namespace Graphics;

void DebuggerTest::Initialize()
{
	GraphicsDevice::Sub.Backgrounds[0]->ColorMode = ColorMode16;
	console = new Console(GraphicsDevice::Sub.Backgrounds[0]);
	AddComponent(console);
	for (int i = 0; i < 64; ++i)
		console->WriteLine(ToStr("Hoi " << i));
	super::Initialize();
}

void DebuggerTest::LoadContent()
{
	super::LoadContent();
}

void DebuggerTest::Update(const GameTime &gameTime)
{
	super::Update(gameTime);
}

void DebuggerTest::Draw(const GameTime &gameTime)
{
	
	super::Draw(gameTime);
}