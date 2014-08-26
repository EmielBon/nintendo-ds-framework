/**
	@class Graphics::Engine

	@author Emiel Bon
 */

#pragma once

#include "types.h"
#include "Background.h"
#include "ObjectAttributeMemory.h"
#include "TextureMemory.h"
#include "ViewPort.h"
#include "RasterizerState.h"
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
		void Synchronize();

		///
		void SetBackgroundColor(u16 color);

	public:

		///
		void Enable3D(bool enable);

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
		
		Array<Background, 4> backgrounds;

	public:

		static GraphicsDevice Main;
		static GraphicsDevice Sub;

	public:

		Ptr<Graphics::BackgroundMemory> BackgroundMemory;
		Ptr<Graphics::SpriteMemory>     SpriteMemory;
		Graphics::ObjectAttributeMemory ObjectAttributeMemory;
		Graphics::TextureMemory    TextureMemory;
		Background &Background0, &Background1, &Background2, &Background3;

	public:

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
}