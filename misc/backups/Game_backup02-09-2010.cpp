#include "Game.h"

#include <nds.h>
#include <stdio.h>
#include "Map.h"
#include "MapLibrary.h"
#include "Zeldaset.h"

#include "Background.h"
#include "TopScreen.h"
#include "BottomScreen.h"
#include "VRAMManager.h"
#include "TileSet.h"

namespace RPG
{
	using namespace Graphics;

	Game::Game()
	{
	}

	Game::~Game()
	{
	}

	Game* Game::GetInstance()
	{
		static Game instance;
		return &instance;
	}

	void Game::Run()
	{
		consoleDemoInit();

		TopScreen* top = TopScreen::GetInstance();

		//set video mode
		top->SetMode(MODE_0_2D);
		top->EnableBackground(0, true);
		
		//map vram to the background
		Background* topBG0 = top->GetBackground(0);
		topBG0->SetVRAMBank('A');
	
		//load our palette
		for(int i = 0; i < 256; ++i)
			BG_PALETTE[i] = zeldasetPal[i];
		
		//get the address of the tile and map blocks 
		//u8* tileMemory = (u8*)BG_TILE_RAM(1);
		//u16* mapMemory0 = (u16*)BG_MAP_RAM(0);
		//u16* mapMemory1 = (u16*)BG_MAP_RAM(1);
		//u16* mapMemory2 = (u16*)BG_MAP_RAM(2);

		//copy the tiles into tile memory one after the other
		//swiCopy(zeldasetTiles, tileMemory, 49152/2);
		TileSet zeldaTiles(zeldasetTiles, Tile16x16, 68, zeldasetPal, 16);

		Map zeldaMap1(MapLibrary::ZeldaMap1(), 4, 17);
		Map zeldaMap2(MapLibrary::ZeldaMap2(), 4, 17);
		Map zeldaMap3(MapLibrary::ZeldaMap3(), 4, 17);

		VRAMManager* vram = VRAMManager::GetInstance();

		vram->AddMap(&zeldaMap1);
		vram->AddMap(&zeldaMap2);
		vram->AddMap(&zeldaMap3);

		vram->AddTileset(zeldasetTiles, 17408);

		topBG0->SetTileBase(1);
		topBG0->SetMapBase(0);

		//SetMap(zeldaMap1,mapMemory0);
		//SetMap(zeldaMap2,mapMemory1);
		//SetMap(zeldaMap3,mapMemory2);

		while(1)
		{
			scanKeys();

			uint32 keys = keysHeld();

			if (keys & KEY_LEFT || keys & KEY_DOWN)
			{
				topBG0->SetMapBase(0);
			}
			else if (keys & KEY_RIGHT)
			{
				topBG0->SetMapBase(1);
			}
			else if (keys & KEY_UP)
			{
				topBG0->SetMapBase(2);
			}

			swiWaitForVBlank();
		}
	}

}