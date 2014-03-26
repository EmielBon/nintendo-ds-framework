#pragma once

#include "types.h"
#include "Size.h"
#include "MapTile.h"
#include "TilesManager.h"
#include "ScreenBlockEntry.h"

namespace Graphics
{
	// todo: rename
	class Map
	{
	public:

		/// Empty constructor
		Map();

		/// Constructor with pointer to this map's BackgroundMemory location
		Map(BackgroundMemory* backgroundMemory, int index);

		///
		bool IsInitialized() const;

		///
		void SetTile(int x, int y, const MapTile &tile);

		/// 
		void SetTile(int index, const MapTile &tile);

		///
		void SetClearTile(const MapTile &tile);

		///
		void Clear();

		///
		Size GetSize() const;

	private:

		ScreenBlockEntry MapTileToScreenBlockEntry(const MapTile &mapTile) const;

	private:

		BackgroundMemory* backgroundMemory;
		int               index;
		Framework::Size   size; 
		u16*              location;
		ScreenBlockEntry  clearTile;
	};

	//-------------------------------------------------------------------------------------------------
	inline Map::Map() : backgroundMemory(NULL), index(-1), size(32, 32), location(NULL)
	{

	}

	//-------------------------------------------------------------------------------------------------
	inline void Map::SetTile(int x, int y, const MapTile &tile)
	{
		SetTile(x + y * size.Width, tile);
	}

	//-------------------------------------------------------------------------------------------------
	inline Size Map::GetSize() const
	{
		return size;
	}

	//-------------------------------------------------------------------------------------------------
	inline bool Map::IsInitialized() const
	{
		return backgroundMemory != NULL && location != NULL && index >= 0;
	}
}