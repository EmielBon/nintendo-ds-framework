#pragma once

#include "TiledImage.h"
#include "types.h"
#include "ScreenBlockEntry.h"

namespace Graphics
{
	class TiledBackground : public TiledImage
	{
	private:
	
		using base = TiledImage;
		
	public:
		
		/// Empty constructor
		TiledBackground() = default;
		
		///
		TiledBackground(int width, int height, int bpp);
		
		/// 
		void SetTileParameters(int index, bool flippedHorizontal, bool flippedVertical, u32 paletteIndex);
		
		/// todo: implement
		static Ptr<TiledBackground> FromTileSet(Ptr<TileSet> tileSet, int width, int height);
		
		///
		void CopyToHardwareBackground(Background &bg) const;
		
	public:
		
		List<ScreenBlockEntry> TileParameters; // This uses the palette index and flip parameters from ScreenBlockEntry. The tile index parameter is ignored. 
	};

	//-------------------------------------------------------------------------------------------------
	inline TiledBackground::TiledBackground(int width, int height, int bpp) : base(width, height, bpp)
	{
		TileParameters.assign(width * height, ScreenBlockEntry());
	}

	//-------------------------------------------------------------------------------------------------
	inline Ptr<TiledBackground> TiledBackground::FromTileSet( Ptr<TileSet> tileSet, int width, int height )
	{
		CRASH("Not implemented"); 
		return nullptr;
	}
	
	//-------------------------------------------------------------------------------------------------
	inline void TiledBackground::SetTileParameters(int index, bool flippedHorizontal, bool flippedVertical, u32 paletteIndex)
	{
		TileParameters[index] = ScreenBlockEntry(0, flippedHorizontal, flippedVertical, paletteIndex);
	}
}