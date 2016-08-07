#pragma once

#include "core/types.h"
#include "graphics/Color.h"

namespace Graphics
{
	class Palette
	{
	public:

		/// Constructor
		Palette() = default;

		/// Constructor for empty palette
		Palette(int size);

		///
		virtual ~Palette() = default;

		/// 
		void AddColor(u16 color);

		///
		void AddColor(float red, float green, float blue);

		/// Returns the number of colors in this palette, excluding the first one if the palette is transparent
		int Count() const;

		///
		bool IsEmpty() const;

	public:
		//////////////////////////////////////////////
		// Todo: Overlap with other data containers //
		//////////////////////////////////////////////
		///
		int GetByteSize() const;

		/// Accessor to the tile data of this tile set
		u16& operator[] (int index);

	public:

		List<u16> Colors;
		bool Transparent;
	};

	//-------------------------------------------------------------------------------------------------
	inline Palette::Palette(int size) : Transparent(true)
	{
		Colors.resize(size);
	}

	//-------------------------------------------------------------------------------------------------
	inline int Palette::Count() const
	{
		int count = Colors.size();
		return (Transparent) ? count - 1 : count;
	}

	//-------------------------------------------------------------------------------------------------
	inline bool Palette::IsEmpty() const
	{
		return Count() == 0;
	}

	//-------------------------------------------------------------------------------------------------
	inline int Palette::GetByteSize() const
	{
		return Colors.size() * sizeof(u16);
	}

	//-------------------------------------------------------------------------------------------------
	inline u16& Palette::operator[] (int index)
	{
		return Colors[index];
	}
}