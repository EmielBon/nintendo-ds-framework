#pragma once

#include "TileSet.h"
#include "types.h"
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

		/// Empty constructor
		Background();

		/// Constructor. The specified index should be unique and in the range [0..3]
		Background(GraphicsDevice *engine, int index);

	public:

		/// Enable this Background, making it visible.
		void Enable();

		/// Disable this Background, making it fully transparent
		void Disable();

		/// Returns whether this background is enabled
		bool IsEnabled() const;

		/// Set this backgrounds draw-priority. A low priority sets this background on top (so draws it last)
		void SetLayer(int priority);

		///
		void ShowMap(int index);

		/// Returns the active map that this background is showing
		Map* GetMap() const;

		/// 
		Graphics::BackgroundMemory& BackgroundMemory() const;

		///
		void Clear();

		/// Gathers all the set options in this Background and puts them in its corresponding Nintendo DS background control register
		void Synchronize() const;		

	private:

		int index;
		int layer;
		bool enabled;

		GraphicsDevice *graphicsDevice;
		int mapIndex;

	public:

		Point Offset;
		Graphics::ColorMode ColorMode;
	};

	//-------------------------------------------------------------------------------------------------
	inline void Background::Enable()
	{
		enabled = true;
	}

	//-------------------------------------------------------------------------------------------------
	inline void Background::Disable()
	{
		enabled = false;
	}

	//-------------------------------------------------------------------------------------------------
	inline bool Background::IsEnabled() const
	{
		return enabled;
	}

	//-------------------------------------------------------------------------------------------------
	inline void Background::SetLayer(int l)
	{
		layer = l;
	}

	//-------------------------------------------------------------------------------------------------
	inline void Background::ShowMap(int index)
	{
		ASSERT(index >= 0 && index < 8, "Map index out of bounds");
		mapIndex = index;
	}
}