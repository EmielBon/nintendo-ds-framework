/**
	@class Graphics::Engine

	@author Emiel Bon
 */

#pragma once

#include "types.h"
#include "ObjectAttributeMemory.h"
#include "ViewPort.h"
#include "RasterizerState.h"
#include "ScreenBlockEntry.h"
#include <nds/arm9/videoGL.h>
#include "fixed.h"

namespace Graphics
{
	enum PrimitiveType 
	{
		TriangleList = GL_TRIANGLES,
		TriangleStrip = GL_TRIANGLE_STRIP,
		QuadList = GL_QUADS,
		QuadStrip = GL_QUAD_STRIP,
	};

	enum ClearOptions 
	{
		Target = 1,
		DepthBuffer = 2,
		Stencil = 4,
	};

	class GraphicsDevice
	{
	protected:

		///
		GraphicsDevice();

	public:

		///
		bool IsMain() const;

		///
		void Initialize();

		/**
		 === Normal modes ===
		 
		 * Properties: 
		 All backgrounds can be tiled and 4bpp, 8bpp or 16bpp colored. (verify?) 
		 All modes support 3D in the main engine
		 Always 4 available backgrounds
		 Background 0 and 1 are always regular
		 Extended can be:
		    - Affine with 16bit map entries (regular + affine mixup)
			- Affine 256 color bitmap
			- Affine direct color bitmap
		 
		 * Modes:
		 Mode 0: 2 and 3 are regular
		 Mode 1: 2 is regular, 3 is affine
		 Mode 2: 2 and 3 are affine
		 Mode 3: 2 is regular, 3 is extended
		 Mode 4: 2 is affine, 3 is extended
		 Mode 5: 2 and 3 are extended

		 * Note: Mode 2-3 display a raw direct color bitmap (15bit RGB values, the upper bit in each halfword is unused), 
		 without any further BG,OBJ,3D layers, these modes are completely bypassing the 2D/3D engines as well as 
		 any 2D effects, however the Master Brightness effect can be applied to these modes. Mode 2 is particulary 
		 useful to display captured 2D/3D images (in that case it can indirectly use the 2D/3D engine).
		 
		 === Special modes ===
		 
		 * Properties: 
		 Main engine only
		 
		 * Modes:
		 Mode 6: 2 backgrounds, 0 is 3D only, 2 is a large bitmap, 1 and 3 are disabled
		 Frame Buffer Mode: Direct VRAM display as bitmap

		 */
		void SetMode(u32 modeIndex);

		///
		void EnableSprites(bool enable);
		
		///
		void Enable3D(bool enable);

		///
		void Synchronize();

		///
		void SetBackgroundColor(u16 color);

		///
		void SetBackground(int index, const TiledBackground &background);

		/// 
		static void SetBackground(Background &bg, const TiledBackground &background);

		/// 
		Background* GetBackgroundAtLayer(int layer) const;

		/// 
		static void SetBackgroundTile(Background &background, int i, int j, Tile *tile, TileParameters params);

		/// 
		void SetTileForBackgroundAtLayer(int layer, int i, int j, Tile *tile, TileParameters params = 0);

		/// Can draw a maximum of 6144 vertices per frame, which corresponds roughly to about 2048 triangles or 1536 quads
		void DrawIndexedPrimitives(PrimitiveType type, int vertexOffset, int minVertexIndex, int numVertices, int startIndex, int primitiveCount);

		/// Can draw a maximum of 6144 vertices per frame, which corresponds roughly to about 2048 triangles or 1536 quads
		void DrawUserIndexedPrimitives(PrimitiveType type, const List<Vertex>& vertices, int vertexOffset, int numVertices, const List<u16> &indices, int indexOffset, int primitiveCount);

		/// Specifies the settings for when the frame buffer will be cleared. Does not actually clear the frame buffer
		void Clear(ClearOptions options, Framework::Color color/*, float depth, int stencil*/);

	protected:

		u32  mode;
		bool enable3D;
		bool enableSprites;

	public:

		static GraphicsDevice Main;
		static GraphicsDevice Sub;

	public:

		Ptr<Graphics::BackgroundMemory> BackgroundMemory;
		Ptr<Graphics::SpriteMemory>     SpriteMemory;
		Graphics::ObjectAttributeMemory ObjectAttributeMemory;
		Ptr<Graphics::TextureMemory>    TextureMemory;
		
	public:

		Array<Background*, 4> Backgrounds;
		Ptr<Graphics::Texture> ActiveTexture;
		Ptr<IndexBuffer> Indices;
		Ptr<Graphics::VertexBuffer> VertexBuffer;
		Graphics::ViewPort ViewPort;
		Graphics::RasterizerState RasterizerState;
	};

	//-------------------------------------------------------------------------------------------------
	inline bool GraphicsDevice::IsMain() const
	{
		return this == &Main;
	}

	//------------------------------------------------------------------------------------------------- 
	inline void GraphicsDevice::SetTileForBackgroundAtLayer(int layer, int i, int j, Tile *tile, TileParameters params /* = 0 */)
	{
		auto bg = GetBackgroundAtLayer(layer);
		sassert(bg, "Background cannot be null");
		SetBackgroundTile(*bg, i, j, tile, params);
	}

	//-------------------------------------------------------------------------------------------------
	inline void GraphicsDevice::SetMode(u32 modeIndex)
	{
		// Main engine has 6 modes, sub engine 5 modes, any number higher is invalid
		sassert(modeIndex >= 0 && modeIndex <= (IsMain() ? 6 : 5), "Error: invalid mode index specified");
		mode = modeIndex;
	}

	//-------------------------------------------------------------------------------------------------
	inline void GraphicsDevice::Enable3D(bool enable)
	{
		sassert(IsMain(), "Error: The sub engine does not support 3D");
		enable3D = enable;
	}

	//-------------------------------------------------------------------------------------------------
	inline void GraphicsDevice::EnableSprites(bool enable)
	{
		enableSprites = enable;
	}
}
