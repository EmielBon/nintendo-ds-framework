#include "TiledBackground.h"
#include "TilesManager.h"
#include "Tile.h"
#include "Debug.h"

namespace Graphics
{
	using namespace FileSystem;

	//-------------------------------------------------------------------------------------------------
	Ptr<TiledBackground> TiledBackground::FromTileSet( Ptr<TileSet> tileSet, int width, int height )
	{

	}

	//-------------------------------------------------------------------------------------------------
	void TiledBackground::Clear()
	{
		IdentifierReferenceCount.clear();
		int entryCount = Size.Width * Size.Height;
		MapTiles.assign(entryCount, MapTile());
		IdentifierReferenceCount[0] = entryCount;
		Bpp = 0;
	}

	//-------------------------------------------------------------------------------------------------
	void TiledBackground::CheckValid() const
	{
		u32 width  = Size.Width;
		u32 height = Size.Height;

		ASSERT2(width  > 0 && width  <= 64 && height > 0 && height <= 64, "Map has invalid dimensions (" << width << "x" << height << ")");
		ASSERT2(MapTiles.size() == width * height, "Map entry count (" << MapTiles.size() << ") does not correspond to map size (" << width << "x" << height << "=" << width * height);
		//ASSERT2(Bpp == 0 || TileByteSize() == Bpp * 64 / 8, "Invalid tile byte size (" << Bpp * 64 / 8 << ")");
	}

	//-------------------------------------------------------------------------------------------------
	void TiledBackground::SetTile( int index, const MapTile& mapTile )
	{
		u32 identifier = mapTile.TileIdentifier;
		u32 oldIdentifier = MapTiles[index].TileIdentifier;

		if (identifier == oldIdentifier)
			return;

		// Assert there are no tiles of different bpp in this map
		int currentTileByteSize = TilesManager::TileForIdentifier(identifier).Bpp;
		ASSERT(Bpp == 0 || identifier == 0 || Bpp == currentTileByteSize, "Map contains tiles of different bit-depths");
		Bpp = currentTileByteSize;
		// Lower the reference count of the old tile that is about to be overwritten
		IdentifierReferenceCount[oldIdentifier]--;
		// Remove tile identifier if there are no references to it
		if (IdentifierReferenceCount[oldIdentifier] == 0)
			IdentifierReferenceCount.erase(oldIdentifier);
		// Set the new tile
		MapTiles[index] = mapTile;
		// Increase the reference count to the new tile's identifier
		if (IdentifierReferenceCount.find(identifier) == IdentifierReferenceCount.end())
		{
			IdentifierReferenceCount[identifier] = 0;
		}
		IdentifierReferenceCount[identifier]++;
	}

	//-------------------------------------------------------------------------------------------------
	Set<u32> TiledBackground::UniqueIndices() const
	{
		Set<u32> uniqueIdentifiers;

		for(auto it = IdentifierReferenceCount.begin(); it != IdentifierReferenceCount.end(); ++it)
		{
			uniqueIdentifiers.insert(it->first);
		}

		return uniqueIdentifiers;
	}

}