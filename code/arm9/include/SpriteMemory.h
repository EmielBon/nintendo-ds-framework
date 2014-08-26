#pragma once

#include "TileMemory.h"
#include "types.h"

namespace Graphics
{
	class SpriteMemory : public TileMemory
	{
	private:

		using super = Graphics::TileMemory;

	public:

		/// 
		SpriteMemory() = delete;

		///
		SpriteMemory(bool isMain);

		///
		void Initialize();

		/// Returns the maximum size of this memory, determined by the physical limit of the Nintendo DS
		int Maximum() const;

		///
		int TileBase() const;

		///
		u16* TileBaseAddress() const;
	};

	//-------------------------------------------------------------------------------------------------
	inline int SpriteMemory::TileBase() const
	{
		return 0; // The SpriteMemory is all tiles (no maps)
	}
}