#pragma once

#include "types.h"
#include "Assert.h"
#include "Vec2.h"
#include <nds/arm9/background.h>
#include "Mat.h"

namespace Graphics
{
	enum ColorMode
	{
		ColorMode16  = BG_COLOR_16,
		ColorMode256 = BG_COLOR_256,
	};

	enum BackgroundType
	{
		Tiled32x32 = BG_32x32,
		Tiled64x32 = BG_64x32,
		Tiled32x64 = BG_32x64,
		Tiled64x64 = BG_64x64,
		TrueColorBitmap128x128 = BG_BMP16_128x128,
		TrueColorBitmap256x256 = BG_BMP16_256x256,
		TrueColorBitmap512x256 = BG_BMP16_512x256,
		TrueColorBitmap512x512 = BG_BMP16_512x512
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
		void Enable();

		///
		void Disable();

		///
		void SetType(BackgroundType type);

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

		/// Gathers all the set options in this Background and puts them in its corresponding Nintendo DS background control register
		void Synchronize();		

		static void SetBackground2Transformation(const Mat<fx8> &transform);

		static void SetBackground3Transformation(const Mat<fx8> &transform);

	private:

		int index;
		int layer;

		GraphicsDevice *graphicsDevice;
		int mapIndex;
		bool isEnabled;
		BackgroundType type;

	public:

		Point Offset;
		Graphics::ColorMode ColorMode;
	};

	//-------------------------------------------------------------------------------------------------
	inline void Background::Enable()
	{
		isEnabled = true;
	}

	//-------------------------------------------------------------------------------------------------
	inline void Background::Disable()
	{
		isEnabled = false;
	}

	//-------------------------------------------------------------------------------------------------
	inline bool Background::IsEnabled() const
	{
		return isEnabled;
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
