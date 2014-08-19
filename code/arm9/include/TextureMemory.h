#pragma once

#include "Memory2D.h"
#include "PaletteMemory.h"
#include "Profiler.h"
#include "types.h"

namespace Graphics
{
	class TextureMemory : public Memory2D
	{
	private:

		using super = Graphics::Memory2D;

	public:

		///
		TextureMemory();

		///
		TextureMemory(bool isMain);

		///
		void Initialize();

		/// Add a complete tile set to VRAM
		void AddTexture(Ptr<Texture> texture);

		/// Returns the tile base indices of this tile set in VRAM
		u16* GetTextureAddress(Ptr<Texture> texture);

		/// Returns this TextureMemory object's maximum size
		int Maximum() const;

	protected:

		///
		bool HasTexture(Ptr<Texture> texture);

		///
		void CopyTextureToVRAM(Ptr<Texture> texture);

	//public:

		//Graphics::PaletteMemory PaletteMemory;

	public:

		u16* nextAvailableAddress;
		Dictionary< Ptr<Texture>, u16* > TextureAddresses;
	};

	//-------------------------------------------------------------------------------------------------
	inline TextureMemory::TextureMemory() : nextAvailableAddress(NULL)
	{

	}
}