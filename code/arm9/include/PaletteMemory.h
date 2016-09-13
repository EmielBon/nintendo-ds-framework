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

		/// 
		PaletteMemory() = delete;

		///
		virtual ~PaletteMemory() = default;

		///
		PaletteMemory(bool isMain, u32 type);

		/// Initialize this PaletteMemory
		void Initialize(u32 parentType);

		/// 
		int AddColor(Color color);

		///
		void SetTransparentColor(Color color);

		///
		bool IsFree(int i) const;

		///
		bool IsFree(int x, int y) const;

		/// Returns the maximum size of this memory, determined by the physical limit of the Nintendo DS's palette memory
		int Maximum() const;

		/// 
		static int IndexForPosition(int x, int y);

		///
		static Point PositionForIndex(int index);

		///
		bool HasColor(Color color) const;

		/// 
		void RegisterPaletteIndexForColor(int paletteIndex, Color color);

		/// 
		int GetIndexForColor(Color color) const;

		/// 
		void SetColorForIndex(Color color, int index);

	protected:
	
		/// 
		int SetColorToNextFreeIndex(Color color);
		
		/// 
		int FindNextFreeIndex();
		
	public:

		u16* location;
		Dictionary< u16, int > ColorToPaletteIndex;
		int currentIndex;
		bool free[256];
	};

	//-------------------------------------------------------------------------------------------------
	finline int PaletteMemory::AddColor(Color color)
	{
		int index = GetIndexForColor(color);
		if (index != -1)
			return index;
		return SetColorToNextFreeIndex(color);
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
	inline void PaletteMemory::SetTransparentColor(Color color)
	{
		location[0] = color;
	}
	
	//-------------------------------------------------------------------------------------------------
	inline bool PaletteMemory::HasColor(Color color) const
	{
		return (GetIndexForColor(color) != -1);
	}
	
	//-------------------------------------------------------------------------------------------------
	inline void PaletteMemory::RegisterPaletteIndexForColor(int paletteIndex, Color color)
	{
		ColorToPaletteIndex[color] = paletteIndex;
	}
	
	//-------------------------------------------------------------------------------------------------
	inline int PaletteMemory::GetIndexForColor(Color color) const
	{
		auto it = ColorToPaletteIndex.find(color);
		return (it == ColorToPaletteIndex.end()) ? -1 : it->second;
	}
}
