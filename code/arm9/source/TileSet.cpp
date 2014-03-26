#include "TileSet.h"
#include "Palette.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	bool TileSet::AddTile(const Tile &tile)
	{
		if (!TileIsCompatible(tile))
			return false;

		Tiles.push_back(tile);
		return true;
	}

	//-------------------------------------------------------------------------------------------------
	bool TileSet::AddPalette(Ptr<Palette> palette)
	{
		if (palette->IsEmpty())
			return false;

		if (Palettes.size() >= 16)
			return false;

		if ( !CompatiblePalette(*palette) ) 
			return false;
		
		Palettes.push_back(palette);
		return true;
	}

	//-------------------------------------------------------------------------------------------------
	bool TileSet::CompatiblePalette(const Palette &palette) const
	{
		return (Palettes.empty() || Palettes[0]->EntryCount() == palette.EntryCount());
	}

	//-------------------------------------------------------------------------------------------------
	List<byte> TileSet::GetPixelData() const
	{
		List<byte> data;

		for(u32 i = 0; i < Tiles.size(); ++i)
		{
			List<byte> pixels = Tiles[i].GetPixelDataRef();
			data.insert(data.end(), pixels.begin(), pixels.end());
		}

		return data;
	}
}