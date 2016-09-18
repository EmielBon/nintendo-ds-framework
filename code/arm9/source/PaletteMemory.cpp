#include "PaletteMemory.h"
#include "Palette.h"
#include "Logging.h"
#include <nds/arm9/video.h>

namespace Graphics
{
	using namespace Debug;
	using namespace Framework;
	
	//-------------------------------------------------------------------------------------------------
	PaletteMemory::PaletteMemory(bool isMain, u32 type) : super(isMain, type), currentIndex(0)
	{
		if (type == Memory_BGPAL || type == Memory_SPRPAL) {
			InitializeWithSize( 256 * sizeof(uint16_t) ); // BG and SPR memory have 256 entries of dedicated palette memory
		}
		
		switch (type)
		{
		case Memory_BGPAL:  location = IsMain() ?     BG_PALETTE :     BG_PALETTE_SUB; break;
		case Memory_SPRPAL: location = IsMain() ? SPRITE_PALETTE : SPRITE_PALETTE_SUB; break;
		case Memory_TEXPAL: location = IsMain() ?         VRAM_E :            nullptr; break; // Todo: VRAM_E is only right in 1 case, derive correct
		default: CRASH("No memory location for palette memory type " << GetType());    break;
		}
		
		// Todo: make dependent on size (and dynamic)
		for (int i = 0; i < 256; ++i) {
			free[i] = true;
		}
	}

	/*printf "Hoi Emiel-Cees\n"
	printf "Ik hou van jou\n"
	printf "Xoxox"*/
	
	//-------------------------------------------------------------------------------------------------
	void PaletteMemory::SetColorForIndex(Color color, int index)
	{
		location[index] = color;
		free[index] = false;
		RegisterPaletteIndexForColor(index, color);
	}
	
	//-------------------------------------------------------------------------------------------------
	int PaletteMemory::SetColorToNextFreeIndex(Color color)
	{
		int index = FindNextFreeIndex();
		SetColorForIndex(color, index);
		return index;
	}
	
	//-------------------------------------------------------------------------------------------------
	int PaletteMemory::FindNextFreeIndex()
	{
		sassert(location, "sss");

		// todo: make upper limit dependent on actual size
		for (int i = 0; i < 256; ++i)
		{
			currentIndex = (currentIndex + i) % 256;
			if (IsFree(currentIndex)) {
				return currentIndex++;
			}
		}
		CRASH("Palette memory full " << currentIndex);
		return -1;
	}
}
