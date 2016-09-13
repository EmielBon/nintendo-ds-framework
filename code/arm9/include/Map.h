#pragma once

#include "types.h"
#include "Size.h"
#include "ScreenBlockEntry.h"

namespace Graphics
{
	class Map
	{
	public:

		/// 
		Map() = delete;

		/// Constructor with pointer to this map's BackgroundMemory location
		Map(Graphics::BackgroundMemory *backgroundMemory, int index);

		///
		bool IsInitialized() const;

		///
		ScreenBlockEntry GetTile(int x, int y) const;

		///
		ScreenBlockEntry GetTile(int index) const;

		///
		void SetTile(int x, int y, ScreenBlockEntry tile);

		/// 
		void SetTile(int index, ScreenBlockEntry tile);

		///
		void Clear();

		///
		Size GetSize() const;

	private:

		int               index;
		Framework::Size   size; 
		u16*              location;
		
	public:

		Graphics::BackgroundMemory *BackgroundMemory;
		ScreenBlockEntry            ClearTile;
	};

	//-------------------------------------------------------------------------------------------------
	inline Size Map::GetSize() const
	{
		return size;
	}

	//-------------------------------------------------------------------------------------------------
	inline bool Map::IsInitialized() const
	{
		return (BackgroundMemory != nullptr && location != nullptr && index >= 0);
	}
	
	//-------------------------------------------------------------------------------------------------
	inline ScreenBlockEntry Map::GetTile(int x, int y) const
	{
		return GetTile(x + y * size.Width);
	}

	//-------------------------------------------------------------------------------------------------
	inline ScreenBlockEntry Map::GetTile(int index) const
	{
		sassert(IsInitialized(), "Setting tile in uninitialized map");
		sassert(index >= 0 && index < size.Width * size.Height, "Internal map index out of bounds");
		return location[index];
	}

	//-------------------------------------------------------------------------------------------------
	inline void Map::SetTile(int x, int y, ScreenBlockEntry tile)
	{
		SetTile(x + y * size.Width, tile);
	}

	//-------------------------------------------------------------------------------------------------
	inline void Map::SetTile(int index, ScreenBlockEntry tile)
	{
		sassert(IsInitialized(), "Setting tile in uninitialized map");
		sassert(index >= 0 && index < size.Width * size.Height, "Internal map index out of bounds");
		location[index] = tile;
	}
}
