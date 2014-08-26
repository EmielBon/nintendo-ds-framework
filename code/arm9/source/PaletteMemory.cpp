#include "PaletteMemory.h"
#include "Palette.h"
#include "Logging.h"
#include <nds/arm9/video.h>

namespace Graphics
{
	using namespace Debug;
	using namespace Framework;
	
	//-------------------------------------------------------------------------------------------------
	PaletteMemory::PaletteMemory(bool isMain, u32 type) : super(isMain, type), currentFreeIndex(0)
	{
		if (GetType() == Memory_BGPAL || type == Memory_SPRPAL)
			InitializeWithSize( 256 * sizeof(u16) ); // BG and SPR memory have 256 entries of dedicated palette memory
		
		switch( GetType() )
		{
		case Memory_BGPAL:  location = IsMain() ?     BG_PALETTE :     BG_PALETTE_SUB; break;
		case Memory_SPRPAL: location = IsMain() ? SPRITE_PALETTE : SPRITE_PALETTE_SUB; break;
		case Memory_TEXPAL: location = IsMain() ?         VRAM_E :            nullptr; break; // Todo: VRAM_E is only right in 1 case, derive correct
		default: CRASH("No memory location for palette memory type " << GetType());    break;
		}

		// Todo: make dependent on size (and dynamic)
		for(int i = 0; i < 256; ++i)
			free[i] = true;
	}

	//-------------------------------------------------------------------------------------------------
	void PaletteMemory::AddPalette(Ptr<Palette> palette)
	{
		auto &colors = palette->Colors;
		for (u32 i = 0; i < colors.size(); ++i)
		{
			if (palette->Transparent && i == 0)
				continue;
			AddColor(colors[i]);
		}
	}

	//-------------------------------------------------------------------------------------------------
	int PaletteMemory::AddDynamicPalette(const List<Ptr<Palette>> &palettes)
	{
		int width  = palettes[0]->Count();
		int height = palettes.size(); 
		int startIndex = FindFreeSequence2D(width, height);
		sassert(startIndex != -1, "No free sequence found!");
		auto pos = PositionForIndex(startIndex);
		
		int i = (palettes[0]->Transparent) ? 1 : 0;
		for (         ; i < width;  ++i)
		for (int j = 0; j < height; ++j)
		{
			int x = pos.x + i;
			int y = pos.y + j;
			auto palette = palettes[j];
			// This can overwrite a duplicate color entry in ColorToPaletteIndex. 
			// However, this is fine for 256 color tiles, since they would just use the new value.
			// It is also fine for 16 color tiles, since they switch vertically by palette number, as long as they retain their 2D start position.
			// It can be problamatic for dynamic palettes if the first palette is used for indexing 
			SetColorForIndex( palette->Colors[i], IndexForPosition(x, y) );
		}
		
		return startIndex;
		/*printf "Hoi Emiel-Cees\n"
		printf "Ik hou van jou\n"
		printf "Xoxox"*/
	}

	//-------------------------------------------------------------------------------------------------
	int PaletteMemory::FindFreeSequence2D(int width, int height /* = 1 */) const
	{
		if (width < 1 || width > 16 || height < 1 || height > 16)
			return -1;

		// Todo: Inefficient
		// Start at 1 because 0 is transparent
		for(int x = 1; x < 16 - width;  ++x)
		for(int y = 0; y < 16 - height; ++y)
		{
			bool found = true;

			for(int xx = 0; xx < width;  ++xx)
			for(int yy = 0; yy < height; ++yy)
				found = found && IsFree(x + xx, y + yy);

			if (found)
				return IndexForPosition(x, y);
		}

		return -1;
	}
	
	//-------------------------------------------------------------------------------------------------
	void PaletteMemory::SetColorForIndex(u16 color, int index)
	{
		location[index] = color;
		free[index] = false;
		RegisterPaletteIndexForColor(color, index);
	}
	
	//-------------------------------------------------------------------------------------------------
	int PaletteMemory::SetColorToNextFreeIndex(u16 color)
	{
		int index = FindNextFreeIndex();
		SetColorForIndex(color, index);
		return index;
	}
	
	//-------------------------------------------------------------------------------------------------
	int PaletteMemory::FindNextFreeIndex()
	{
		// todo: make upper limit dependent on actual size
		for (int i = 0; i < 256; ++i)
		{
			int index = (currentFreeIndex + i) % 256;
			currentFreeIndex = (currentFreeIndex + 1) % 256;
			if (IsFree(index))
			{
				return index;
			}
			else
			{
				ASSERT(location, "sss");
				CRASH(index);
			}
		}
		CRASH("Palette memory full " << currentFreeIndex);
		return -1;
		/*while(!IsFree(currentFreeIndex))
			currentFreeIndex++;
		return currentFreeIndex;*/
	}
}