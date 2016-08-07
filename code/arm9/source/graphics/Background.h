#pragma once

#include "TileSet.h"
#include "core/types.h"
#include "Assert.h"
#include "Vec2.h"
#include <nds/arm9/background.h>

namespace Graphics
{
	enum ColorMode
	{
		ColorMode16  = BG_COLOR_16,
		ColorMode256 = BG_COLOR_256,
	};

	class Background
	{
	public:

		/// 
		Background() = delete;

		/// Constructor. The specified index should be unique and in the range [0..3]
		Background(GraphicsDevice *engine, int index);

	public:

		/// Returns whether this background is enabled
		bool IsEnabled() const;

		/// 
		int GetLayer() const;

		/// Set this backgrounds draw-priority. A low priority sets this background on top (so draws it last)
		void SetLayer(int priority);

		/// 
		int GetMapIndex() const;

		///
		Map* GetMap() const;

		///
		void ShowMapWithIndex(int index);

		/// todo: can this be removed?
		Graphics::BackgroundMemory& BackgroundMemory() const;

		///
		void Clear();

		/// Gathers all the set options in this Background and puts them in its corresponding Nintendo DS background control register
		void Synchronize() const;		

	private:

		int index;
		int layer;

		GraphicsDevice *graphicsDevice;
		int mapIndex;

	public:

		Point Offset;
		Graphics::ColorMode ColorMode;
	};

	//-------------------------------------------------------------------------------------------------
	inline bool Background::IsEnabled() const
	{
		return mapIndex >= 0;
	}

	//-------------------------------------------------------------------------------------------------
	inline int Background::GetLayer() const
	{
		return layer;
	}

	//-------------------------------------------------------------------------------------------------
	inline void Background::SetLayer(int l)
	{
		sassert(l >= 0 && l <= 3, "Layer index out of range");
		layer = l;
	}

	//-------------------------------------------------------------------------------------------------
	inline int Background::GetMapIndex() const
	{
		return mapIndex;
	}

	//-------------------------------------------------------------------------------------------------
	inline void Background::ShowMapWithIndex(int index)
	{
		ASSERT(index >= 0 && index < 8, "Map index out of bounds");
		mapIndex = index;
	}
}