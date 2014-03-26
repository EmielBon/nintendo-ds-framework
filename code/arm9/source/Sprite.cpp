#include "Sprite.h"
#include "MathFunctions.h"
#include "Logging.h"
#include "TileSet256.h"
#include "TilesManager.h"

namespace Graphics
{
	using namespace Math;

	//-------------------------------------------------------------------------------------------------
	Sprite::Sprite(const List<SpriteSubImage> &subImages) : X(0), Y(0), Scale(1.0f), Priority(OBJPRIORITY_0), SubImageIndex(0), ImageSpeed(1), SubImages(subImages), size(OBJSIZE_8), shape(OBJSHAPE_SQUARE)
	{
		int width  = subImages[0].Width * 8;
		int height = subImages[0].Height * 8;

		int majorSize = Max(width, height);
		
		switch (majorSize)
		{
		case  8: size = OBJSIZE_8;  break;
		case 16: size = OBJSIZE_16; break;
		case 32: size = OBJSIZE_32; break;
		case 64: size = OBJSIZE_64; break;
		default: ASSERT(false, "Error: Invalid sprite size"); break;
		}

		if (width == height)
			shape = OBJSHAPE_SQUARE;
		/*
		 * Other shapes currently unsupported
		 *
		if (width > height)
			shape = OBJSHAPE_WIDE;
		if (width < height)
			shape = OBJSHAPE_TALL;
		 */
		ApplyChanges();
	}

	//-------------------------------------------------------------------------------------------------
	void Sprite::ApplyChanges()
	{
		UniqueIndices.clear();

		// Build the set of unique tile indices
		for(auto it = SubImages.begin(); it != SubImages.end(); ++it)
		{	
			SpriteSubImage& subImage = *it;
			for(int i = 0; i < subImage.TileCount(); ++i)
				UniqueIndices.insert(subImage.TileIdentifiers[i]);
		}
	}
}