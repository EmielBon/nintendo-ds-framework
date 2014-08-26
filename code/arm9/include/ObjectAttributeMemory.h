#pragma once

#include "types.h"
#include <nds/arm9/sprite.h>

namespace Graphics
{
	class GraphicsDevice;

	enum SpriteDisplayMode
	{
		SpriteDisplayMode_1D_32  = DISPLAY_SPR_1D | DISPLAY_SPR_1D_SIZE_32,
		SpriteDisplayMode_1D_64  = DISPLAY_SPR_1D | DISPLAY_SPR_1D_SIZE_64,
		SpriteDisplayMode_1D_128 = DISPLAY_SPR_1D | DISPLAY_SPR_1D_SIZE_128,
		SpriteDisplayMode_1D_256 = DISPLAY_SPR_1D | DISPLAY_SPR_1D_SIZE_256,
	};

	class ObjectAttributeMemory
	{
	public:

		/// Empty constructor
		ObjectAttributeMemory();

		///
		ObjectAttributeMemory(GraphicsDevice *device);

		/// Update the Nintendo DS's OAM attributes with the possibly changed Sprite properties
		void Update();

		/// Adds a sprite to the Nintendo DS's OAM memory 
		void DrawSprite(Ptr<Sprite> sprite, fx12 x, fx12 y, fx12 subImageIndex);

		/// Clears all sprite entries
		void Reset();

		///
		Ptr<LLR::SpriteResource> Convert(const Sprite &sprite) const;

	private:

		/// Get the offset to multiply the gfx index for a SpriteEntry with (depends on the display mode)
		int GetSpriteTileStride();

	public:

		/*
		 * There are only 10 bits in each sprite's control register to specify where the graphics for a sprite begins.
		 * 10 bits gives us 1024 unique offsets into sprite graphics memory (2^10). 
		 * The boundary size is simply how much we multiply this 10 bit offset by to specify the start of the sprite graphics (tiled or bitmaped, 2D or 1D). 
		 * Because the boundary size specifies how fine of a grain your sprite graphics can be located in sprite graphics memory having a boundary size very 
		 * big might leave empty holes if you have lots of small sprites. However, boundary size directly affects how much sprite graphics memory you can 
		 * access: A boundary size of 32 will allow you to address 32KB of vram (32bytes boundary * 1024 offsets), boundary size of 64 will allow 64KB of 
		 * vram ect...
		 *
		 * A good rule of thumb for picking the boundary size is to simply match it to the amount of vram you have allocated to sprites. 
		 * If you have a 128KB vram bank allocated to sprite graphics using anything less than a boundary size of 128 will prevent you from accessing the 
		 * entire bank for sprite graphics, anything more doesn't really get you anything either. 
		 * http://devkitpro.org/viewtopic.php?f=6&t=230
		 */
		// Todo: Different name?
		// Todo: change to libnds' SpriteMapping enum... or not if that has no use outside the libnds OAM api
		SpriteDisplayMode DisplayMode;

	protected:

		GraphicsDevice* graphicsDevice;
		OAMTable* oam;
		u16* location;

		const static u32 SPRITE_MAX = 128;
		const static u32 SPRITE_MAX_AFFINE = 32;
		
		List< Ptr<Sprite> > sprites;
		Dictionary< Ptr<Sprite>, Ptr<LLR::SpriteResource> > oamSpriteMap;
	};

	//-------------------------------------------------------------------------------------------------
	inline ObjectAttributeMemory::ObjectAttributeMemory() : DisplayMode(SpriteDisplayMode_1D_64), graphicsDevice(nullptr), oam(nullptr), location(nullptr)
	{
		
	}
}