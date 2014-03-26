#include "PaletteMemory.h"
#include "Palette.h"
#include "Logging.h"
#include <nds/arm9/video.h>

namespace Graphics
{
	using namespace Debug;
	using namespace Framework;
	
	//-------------------------------------------------------------------------------------------------
	PaletteMemory::PaletteMemory(bool isMain, u32 type) : super(isMain, type)
	{
		if (GetType() == Memory_BGPAL || type == Memory_SPRPAL)
			InitializeWithSize( 256 * sizeof(u16) ); // BG and SPR memory have 256 entries of dedicated palette memory
		
		switch( GetType() )
		{
		case Memory_BGPAL:  location = IsMain() ?     BG_PALETTE :     BG_PALETTE_SUB; break;
		case Memory_SPRPAL: location = IsMain() ? SPRITE_PALETTE : SPRITE_PALETTE_SUB; break;
		case Memory_TEXPAL: location = IsMain() ?         VRAM_E :               NULL; break; // Todo: VRAM_E is only right in 1 case, derive correct
		default:            location = NULL;                                           break;
		}

		// Todo: make dependent on size (and dynamic)
		for(int i = 0; i < 256; ++i)
			free[i] = true;
	}

	//-------------------------------------------------------------------------------------------------
	void PaletteMemory::AddPalette(Ptr<Palette> palette, bool transparent)
	{
		if (HasPalette(palette)) // Palette is already in this memory
			return;

		int count = palette->EntryCount();
		int index = FindFreeSequence(transparent ? count - 1 : count);

		ASSERT2(index != -1, "No free sequence of " << count << " found!");

		CopyPalette(palette, index, transparent);
	}

	//-------------------------------------------------------------------------------------------------
	void PaletteMemory::AddDynamicPalette(const List<Ptr<Palette>> &palettes, bool transparent)
	{
		if (palettes.size() == 0)
			return;
		
		// Todo: Assumption that all sub-palettes are present in palette ram if the first one is
		if (HasPalette(palettes[0])) // Palette is already in this memory
			return;

		int count = palettes[0]->EntryCount();
		int index = FindFreeSequence2D(transparent ? count - 1 : count, palettes.size());

		ASSERT(index != -1, "No free sequence found!");

		for(u32 i = 0; i < palettes.size(); ++i)
			CopyPalette(palettes[i], index + 16 * i, transparent);
	}

	//-------------------------------------------------------------------------------------------------
	bool PaletteMemory::Invalidate(Ptr<Palette> palette)
	{
		if (!HasPalette(palette))
			return false;

		int index = GetIndex(palette);

		for(int i = 0; i < palette->EntryCount(); ++i)
		{
			free[index + i] = true;
		}
		indexMap.erase(palette);
		return true;
	}

	//-------------------------------------------------------------------------------------------------
	int PaletteMemory::FindFreeSequence(int width) const
	{
		if (width < 1 || width > 256)
			return -1;

		int index = 1;
		int counter = 0;

		// Start at 1 because 0 is transparent
		for(int i = 1; i < 256; ++i)
		{
			if ( IsFree(i) )
			{
				counter++;
			}
			else
			{
				if (i >= 256 - width) // Impossible to fit
					break;

				counter = 0;
				index = i + 1;
			}

			if (counter == width)
				return index;
		}

		return -1;
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
			{
				found = found && IsFree(x + xx, y + yy);
			}

			if (found)
				return IndexForPosition(x, y);
		}

		return -1;
	}

	//-------------------------------------------------------------------------------------------------
	void PaletteMemory::CopyPalette(Ptr<Palette> palette, int index, bool transparent)
	{
		List<u16> entries = (transparent) ? List<u16>(palette->Entries.begin() + 1, palette->Entries.end()) 
			                               : palette->Entries;

		ASSERT(location != NULL, "Copy data to NULL");

		bool success = Add(entries, location + index);

		ASSERT(success, "Failed to copy palette");

		for(int i = 0; i < palette->EntryCount(transparent); ++i)
		{
			free[index + i] = false;
		}

		indexMap[palette] = (transparent) ? index - 1 : index;
	}

	//-------------------------------------------------------------------------------------------------
	int PaletteMemory::GetIndex(Ptr<Palette> palette)
	{
		if (!HasPalette(palette)) 
			return -1; // Palette not in memory
		return indexMap[palette];
	}

	//-------------------------------------------------------------------------------------------------
	Point PaletteMemory::GetPosition(Ptr<Palette> palette)
	{
		if (!HasPalette(palette)) 
			return Point(-1, 0); // Palette not in memory
		return PositionForIndex(indexMap[palette]);
	}
}