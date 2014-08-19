#pragma once

#include "Memory2D.h"
#include "Profiler.h"
#include "Palette.h"
#include "types.h"
#include "Vec2.h"
// Todo: PaletteMemory actually has 2 slots (more?), the first one is dedicated palette memory, the second can be used by allocating a small VRAM Bank

namespace Graphics
{
	class PaletteMemory : public Memory2D
	{
	private:

		friend class BackgroundMemory;
		friend class SpriteMemory;
		friend class TextureMemory;
		using super = Graphics::Memory2D;

	public:

		/// Empty Constructor
		PaletteMemory();

		///
		PaletteMemory(bool isMain, u32 type);

		/// Initialize this PaletteMemory
		void Initialize(u32 parentType);

		/// Returns whether this palette is present in palette memory
		bool HasPalette(Ptr<Palette> palette);

		/// Add a Palette to the Nintendo DS's PaletteMemory, returns the needed pixel offset if successful, and -1 otherwise
		void AddPalette(Ptr<Palette> palette, bool transparent);

		/// Add a Palette to the Nintendo DS's PaletteMemory, returns the needed horizontal pixel offset if successful, and -1 otherwise 
		void AddDynamicPalette(const List<Ptr<Palette>> &palettes, bool transparent);

		/// Marks a palette for removal, freeing up its used space
		bool Invalidate(Ptr<Palette> palette);

		///
		void SetTransparentColor(u16 color);

		/// 
		void CopyPalette(Ptr<Palette> palette, int index, bool transparent);

		/// Finds the index at which a sequence with a specified size can be placed in 256x1 palette memory
		/// Returns a number in the range [1, 255]. Index 0 is the transparent color so it is skipped
		int FindFreeSequence(int width) const;

		/// Finds the index at which a sequence with the given width and height can be placed in 16x16 palette memory
		/// Returns a number in the range [1, 255]. The column 1x16 contains the transparent colors for every 16x1 palette, so it is skipped
		int FindFreeSequence2D(int width, int height = 1) const;

		///
		bool IsFree(int i) const;

		///
		bool IsFree(int x, int y) const;

		///
		int GetIndex(Ptr<Palette> palette);

		///
		Point GetPosition(Ptr<Palette> palette);

		/// Returns the maximum size of this memory, determined by the physical limit of the Nintendo DS's palette memory
		int Maximum() const;

		/// 
		static int IndexForPosition(int x, int y);

		///
		static Point PositionForIndex(int index);

	protected:

		u16* location;
		Dictionary< Ptr<Palette>, int> indexMap;
		bool free[256];
	};

	//-------------------------------------------------------------------------------------------------
	inline PaletteMemory::PaletteMemory() : location(NULL)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline int PaletteMemory::Maximum() const
	{
		// The same size for all palettes
		// 0x200 = hex representation of 256 16-bit entries = 512 bytes
		// Todo: - Include expanded size when expansion is implemented
		return 0x200;
	}

	//-------------------------------------------------------------------------------------------------
	inline bool PaletteMemory::IsFree(int i) const
	{
		// Todo: account for expansion once it is implemented
		sassert(i >= 0 || i < 256, "Error: Index %i is out of range", i);
		return free[i];
	}

	//-------------------------------------------------------------------------------------------------
	inline bool PaletteMemory::IsFree(int x, int y) const
	{
		return IsFree( IndexForPosition(x, y) );
	}

	//-------------------------------------------------------------------------------------------------
	inline int PaletteMemory::IndexForPosition(int x, int y)
	{
		sassert(x >= 0 && x < 16 && y >= 0 && y < 16, "Error: Position (%i,%i) out of range", x, y);
		return x + y * 16;
	}

	//-------------------------------------------------------------------------------------------------
	inline Framework::Point PaletteMemory::PositionForIndex(int index)
	{
		sassert(index >= 0 || index < 256, "Error: Index %i is out of range", index);
		return Point(index % 16, index / 16);
	}

	//-------------------------------------------------------------------------------------------------
	inline bool PaletteMemory::HasPalette(Ptr<Palette> palette)
	{
		sassert(palette, "Palette is null");
		return indexMap.find(palette) != indexMap.end();
	}

	//-------------------------------------------------------------------------------------------------
	inline void PaletteMemory::SetTransparentColor(u16 color)
	{
		location[0] = color;
	}
}