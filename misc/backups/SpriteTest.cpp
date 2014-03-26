/*#include "SpriteTest.h"

#include <nds.h>
#include <stdio.h>
#include <LinkSheet.h>

namespace RPG
{
	struct Link
	{
		int x;
		int y;

		u16* sprite_gfx_mem[12];
		int gfx_frame;

		int state;
		int n;
		int anim_frame;
		bool shield;
	};

	void SpriteTest::Run()
	{
		consoleDemoInit();
		//---------------------------------------------------------------------
		// The womman sprite
		// she needs an array of pointers to sprite memory since all 
		// her frames are to be loaded.
		// she also needs to keep track of which sprite memory pointer is in use
		//---------------------------------------------------------------------
		

		//---------------------------------------------------------------------
		// Initializing a link requires us to load all of her graphics frames 
		// into memory
		//---------------------------------------------------------------------
		Link link = {0,0};
		

		videoSetMode(MODE_0_2D);

		vramSetBankA(VRAM_A_MAIN_SPRITE);

		oamInit(&oamMain, SpriteMapping_1D_128, false);

		u8* gfx = (u8*) linkTiles;

		for(int i = 0; i < 56; ++i)
		{
			link.sprite_gfx_mem[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
			dmaCopy(gfx, link.sprite_gfx_mem[i], 32*32);
			gfx += 32*32;
		}

		dmaCopy(linkPal, SPRITE_PALETTE, 512);	
		link.shield = false;
		int equip = 0;
		while(1) 
		{
			scanKeys();
			bool animate = false;
			int keys = keysHeld();
			if(keys)
			{
				if(keys & KEY_DOWN)
				if(link.y < SCREEN_HEIGHT - 24)
				{
					link.y++;
					link.state = 0;
					animate = true;
				}
				if(keys & KEY_UP)
				if(link.y > -2)
				{
					link.y--;
					link.state = 1;
					animate = true;
				}
				if(keys & KEY_RIGHT)
				if(link.x <SCREEN_WIDTH - 24)
				{
					link.x++;
					link.state = 2;
					animate = true;

				}
				if(keys & KEY_LEFT) 
				if(link.x > -6)
				{
					link.x--;
					link.state = 3;
					animate = true;

				}
				if(keys & KEY_A)
				{
					link.shield = !link.shield;
					if(link.shield)
						equip = 28;
					else
						equip = 0;
				}

			}
			if(animate) link.gfx_frame++;
			else link.gfx_frame = 0;
			if(link.gfx_frame >8*6 ) link.gfx_frame = 0;
			//-----------------------------------------------------------------
			// Set oam attributes, notice the only difference is in the sprite 
			// graphics memory pointer argument.  The man only has one pointer
			// while the women has an array of pointers
			//-----------------------------------------------------------------
			link.n = link.gfx_frame/8 + link.state*7 + equip;
			oamSet(&oamMain, 0, link.x, link.y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 
				link.sprite_gfx_mem[link.n], -1, false, false, false, false, false);

			swiWaitForVBlank();

			oamUpdate(&oamMain);
		}
	}
}
*/