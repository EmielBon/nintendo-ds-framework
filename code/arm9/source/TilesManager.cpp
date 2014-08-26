/*#include "TilesManager.h"
#include "Assert.h"
#include "TileSet.h"

namespace Graphics
{
	Dictionary< Ptr<TileSet>, u32 > TilesManager::TileSetToIdentifier;
	u32                             TilesManager::nextFreeIdentifier = 0;

	//-------------------------------------------------------------------------------------------------
	void TilesManager::AddTileSet( Ptr<TileSet> tileSet )
	{
		ASSERT(TileSetToIdentifier.find(tileSet) == TileSetToIdentifier.end(), "Cannot add tileset twice");
		TileSetToIdentifier[tileSet] = nextFreeIdentifier;
		nextFreeIdentifier += tileSet->GetTileCount8x8();
	}

	//-------------------------------------------------------------------------------------------------
	u32 TilesManager::IdentifierForTileSet( Ptr<TileSet> tileSet )
	{
		ASSERT(tileSet != nullptr, "Requesting identifier for null tileset");
		ASSERT(TileSetToIdentifier.find(tileSet) != TileSetToIdentifier.end(), "Unknown TileSet");
		return TileSetToIdentifier[tileSet];
	}

	//-------------------------------------------------------------------------------------------------
	u32 TilesManager::IdentifierForTile( Ptr<TileSet> tileSet, u32 tileIndex )
	{
		ASSERT2(tileIndex < (u32)tileSet->GetTileCount8x8(), "Index out of range: " << tileIndex << " " << tileSet->GetTileCount8x8());
		return IdentifierForTileSet(tileSet) + tileIndex;
	}

	//-------------------------------------------------------------------------------------------------
	Ptr<TileSet> TilesManager::TileSetForIdentifier( u32 identifier )
	{
		for(auto it = TileSetToIdentifier.begin(); it != TileSetToIdentifier.end(); ++it)
		{
			Ptr<TileSet> tileSet = it->first;
			u32 tileSetId        = it->second;

			if (identifier >= tileSetId && identifier < tileSetId + tileSet->GetTileCount8x8())
				return tileSet;
		}
		return nullptr;
	}

	//-------------------------------------------------------------------------------------------------
	Tile& TilesManager::TileForIdentifier( u32 identifier )
	{
		Ptr<TileSet> tileSet = TileSetForIdentifier(identifier);
		return tileSet->Tiles[identifier - IdentifierForTileSet(tileSet)];
	}

}*/