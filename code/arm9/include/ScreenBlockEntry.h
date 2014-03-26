#pragma once

#include "types.h"
#include "Debug.h"
#include <nds/arm9/background.h>

namespace Graphics
{
	struct ScreenBlockEntry
	{
	public:

		ScreenBlockEntry();

		ScreenBlockEntry(u16 value);

		ScreenBlockEntry(u16 tileIndex, bool flippedHorizontal, bool flippedVertical, u16 paletteIndex);
	
		int TileIndex();

		void SetTileIndex(int index);

		bool IsFlippedHorizontal() const;

		void FlipHorizontal(bool flip);

		bool IsFlippedVertical() const;

		void FlipVertical(bool flip);

		int PaletteIndex() const;

		// Todo: using indices kinda sucks, change to actual palette?
		void SetPaletteIndex(int index);

		operator u16();
	
	private:

		u16 value;
	};

	//-------------------------------------------------------------------------------------------------
	finline ScreenBlockEntry::ScreenBlockEntry() : value(0) 
	{  
	};

	//-------------------------------------------------------------------------------------------------
	finline ScreenBlockEntry::ScreenBlockEntry(u16 v) : value(v) 
	{ 
	};
	
	//-------------------------------------------------------------------------------------------------
	finline ScreenBlockEntry::ScreenBlockEntry(u16 tileIndex, bool flippedHorizontal, bool flippedVertical, u16 paletteIndex) : value(0)
	{
		ASSERT(tileIndex >= 0, "Negative tile index");
		ASSERT(paletteIndex >= 0 && paletteIndex < 16, "Palette index out of bounds");

		// todo: compose in one step
		SetTileIndex(tileIndex);
		FlipHorizontal(flippedHorizontal);
		FlipVertical(flippedVertical);
		SetPaletteIndex(paletteIndex);

		//value = (tileIndex) |
		//	(flippedHorizontal) ? TILE_FLIP_H : 0 |
		//	(flippedVertical)   ? TILE_FLIP_V : 0 |
		//	TILE_PALETTE(paletteIndex);

		ASSERT2(tileIndex == TileIndex(), "Error 1: " << tileIndex << " " << (value & 0x3FF)); 
		ASSERT(flippedHorizontal == IsFlippedHorizontal(), "Error 2"); 
		ASSERT(flippedVertical == IsFlippedVertical(), "Error 3"); 
		ASSERT(paletteIndex == PaletteIndex(), "Error 4");
	}

	//-------------------------------------------------------------------------------------------------
	inline ScreenBlockEntry::operator u16() 
	{ 
		return value; 
	};

	//-------------------------------------------------------------------------------------------------
	inline int ScreenBlockEntry::PaletteIndex() const
	{
		return ((value >> 12) & 0xF);
	}

	//-------------------------------------------------------------------------------------------------
	finline void ScreenBlockEntry::SetPaletteIndex(int index)
	{
		ASSERT2(index >= 0 && index < 16, "Palette index out of range (" << index << ")");
		value = (value & 0xFFF) | TILE_PALETTE(index);
	}

	//-------------------------------------------------------------------------------------------------
	inline int ScreenBlockEntry::TileIndex()
	{
		return (value & 0x3FF);
	}

	//-------------------------------------------------------------------------------------------------
	finline void ScreenBlockEntry::SetTileIndex(int index)
	{
		ASSERT2(index >= 0 && index < 1024, "Tile index out of range (" << index << ")");
		value = index | (value & 0xFC00);
	}

	//-------------------------------------------------------------------------------------------------
	inline bool ScreenBlockEntry::IsFlippedHorizontal() const
	{
		return (value >> 10) & 1;
	}
	
	//-------------------------------------------------------------------------------------------------
	finline void ScreenBlockEntry::FlipHorizontal(bool flip)
	{
		value = (flip) ? (value | TILE_FLIP_H) : (value & ~(TILE_FLIP_H));
// 		if (flip) value |= TILE_FLIP_H;
// 		else      value &= ~(TILE_FLIP_H);
	}

	//-------------------------------------------------------------------------------------------------
	inline bool ScreenBlockEntry::IsFlippedVertical() const
	{
		return (value >> 11) & 1;
	}

	//-------------------------------------------------------------------------------------------------
	finline void ScreenBlockEntry::FlipVertical(bool flip)
	{
		value = (flip) ? (value | TILE_FLIP_V) : (value & ~(TILE_FLIP_V));
// 		if (flip) value |= TILE_FLIP_V;
// 		else      value &= ~(TILE_FLIP_V);
	}
}