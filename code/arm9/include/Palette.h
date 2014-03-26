#pragma once

#include "types.h"
#include "Color.h"

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

		/// 
		int EntryCount(bool transparent = false) const;

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

		List<u16> Entries;
	};

	//-------------------------------------------------------------------------------------------------
	inline Palette::Palette(int size)
	{
		Entries.resize(size);
	}

	//-------------------------------------------------------------------------------------------------
	inline int Palette::EntryCount(bool transparent) const
	{
		int entries = Entries.size();
		return (transparent) ? entries -1 : entries;
	}

	//-------------------------------------------------------------------------------------------------
	inline bool Palette::IsEmpty() const
	{
		return EntryCount() == 0;
	}

	//-------------------------------------------------------------------------------------------------
	inline int Palette::GetByteSize() const
	{
		return Entries.size() * sizeof(u16);
	}

	//-------------------------------------------------------------------------------------------------
	inline u16& Palette::operator[] (int index)
	{
		return Entries[index];
	}
}