#include "GraphicsDevice.h"

#include "types.h"
#include "Screen.h"
#include "Color.h"

// 2D Graphics
#include "Background.h"
#include "BackgroundMemory.h"
#include "SpriteMemory.h"

// 3D Graphics
#include "OpenGL.h"
#include "Vertex.h"
#include "EfficientVertex.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "TextureMemory.h"

// Utils
#include "MathFunctions.h"

// Debugging
#include "Debug.h"

// libnds
#include <nds/arm9/video.h>

namespace Graphics
{
	GraphicsDevice GraphicsDevice::Main;
	GraphicsDevice GraphicsDevice::Sub;

	//-------------------------------------------------------------------------------------------------
	GraphicsDevice::GraphicsDevice() : mode(0), enable3D(false), enableSprites(false)
	{
		// Do not call Initialize() here, the order of initialization is 
		// important so Initialize() is manually called in Game::Run()!
		ViewPort = Graphics::ViewPort(0, 0, Screen::Width-1, Screen::Height-1);
	}

	//-------------------------------------------------------------------------------------------------
	void GraphicsDevice::Initialize()
	{
		for(u32 i = 0; i < Backgrounds.size(); ++i)
			Backgrounds[i] = new Background(this, i);

		bool main = IsMain();

		BackgroundMemory      = New<Graphics::BackgroundMemory>(main);
		SpriteMemory          = New<Graphics::SpriteMemory>(main);
		ObjectAttributeMemory = Graphics::ObjectAttributeMemory(this);
		TextureMemory         = New<Graphics::TextureMemory>(main);

		BackgroundMemory->Initialize();
		SpriteMemory->Initialize();
		TextureMemory->Initialize();
	}

	//-------------------------------------------------------------------------------------------------
	void GraphicsDevice::SetMode(u32 modeIndex)
	{
		// Main engine has 6 modes, sub engine 5 modes, any number higher is invalid
		sassert(modeIndex >= 0 && modeIndex <= (IsMain() ? 6 : 5), "Error: invalid mode index specified");
		mode = modeIndex;
	}

	//-------------------------------------------------------------------------------------------------
	void GraphicsDevice::Enable3D(bool enable)
	{
		sassert(IsMain(), "Error: The sub engine does not support 3D");
		enable3D = enable;
	}

	//-------------------------------------------------------------------------------------------------
	void GraphicsDevice::EnableSprites(bool enable)
	{
		enableSprites = enable;
	}

	//-------------------------------------------------------------------------------------------------
	void GraphicsDevice::Synchronize()
	{
		// This number is based on libnds 1.4.8's MODE_0_2D
		u32 videoMode = 0x10000;

		videoMode += mode;

		for(u32 i = 0; i < Backgrounds.size(); ++i)
			Backgrounds[i]->Synchronize();
			
		// These bit masks are based on libnds 1.4.8 DISPLAY_BGx_ACTIVE, which are bit 8 through 11 of the video mode
		for(u32 i = 0; i < Backgrounds.size(); ++i)
			videoMode |= ( Backgrounds[i]->IsEnabled() ) ? BIT(8 + i) : 0;

		videoMode |= (enable3D) ? ENABLE_3D : 0;
		videoMode |= (enableSprites) ? DISPLAY_SPR_ACTIVE | ObjectAttributeMemory.DisplayMode : 0;

		if ( IsMain() )
			videoSetMode(videoMode);
		else
			videoSetModeSub(videoMode);

		ObjectAttributeMemory.Update();
	}

	//-------------------------------------------------------------------------------------------------
	void GraphicsDevice::SetBackgroundColor(u16 color)
	{
		BackgroundMemory->PaletteMemory->SetTransparentColor(color);
	}

	//-------------------------------------------------------------------------------------------------
	Background* GraphicsDevice::GetBackgroundAtLayer(int layer) const
	{
		for (auto background : Backgrounds)
			if (background->GetLayer() == layer)
				return background;
		return nullptr;
	}

	//------------------------------------------------------------------------------------------------- 
	void GraphicsDevice::SetBackgroundTile(Background &background, int i, int j, Tile *tile, TileParameters params /* = 0 */)
	{
		auto &bgMem = background.BackgroundMemory();
		auto &map   = *bgMem.Maps[background.GetMapIndex()];

		if (tile)
		{
			u32 tileIndex = bgMem.AddTile(*tile);
			auto screenBlockEntry = params;
			screenBlockEntry.SetTileIndex(tileIndex);
			map.SetTile(i, j, screenBlockEntry);
		}
		else
		{
			map.SetTile(i, j, map.ClearTile);
		}
	}

	//-------------------------------------------------------------------------------------------------
	void GraphicsDevice::DrawSprite(const Sprite &sprite, fx12 x, fx12 y, fx12 imageIndex, fx8 horizontalScale /* = 1 */, fx8 verticalScale /* = 1 */)
	{
		SpriteMemory->AddSprite(sprite);
		ObjectAttributeMemory.DrawSprite(sprite, x, y, imageIndex, horizontalScale, verticalScale);
	}

	//-------------------------------------------------------------------------------------------------
	void GraphicsDevice::DrawIndexedPrimitives( PrimitiveType type, int vertexOffset, int minVertexIndex, int numVertices, int startIndex, int primitiveCount )
	{
		sassert(IsMain(), "Error: The sub engine does not support 3D");
		sassert(VertexBuffer, "Error: No vertex buffer assigned");
		sassert(Indices, "Error: No index buffer assigned");
		sassert(Indices->IndexCount() > 0, "Error: Drawing empty index list");

		glBegin((GL_GLBEGIN_ENUM)type);

		for(int i = startIndex; i < Indices->IndexCount(); ++i)
		{
			int index = Indices->GetData()[i] + vertexOffset;
			const EfficientVertex &v = VertexBuffer->GetData()[index];

			glTexCoord2fx12(v.U, v.V);
			GFX_NORMAL = v.Normal;
			GFX_VERTEX16 = v.XY;
			GFX_VERTEX16 = v.Z;
		}

		glPopMatrix(1);
	}

	//-------------------------------------------------------------------------------------------------
	void GraphicsDevice::DrawUserIndexedPrimitives( PrimitiveType type, const List<Vertex>& vertices, int vertexOffset, int numVertices, const List<u16> &indices, int indexOffset, int primitiveCount )
	{
		sassert(IsMain(), "Error: The sub engine does not support 3D");
		sassert(vertices.size() > 0 && indices.size() > 0, "Error: Drawing empty vertices and/or indices list");

		glBegin((GL_GLBEGIN_ENUM)type);

		for(u32 i = indexOffset; i < indices.size(); ++i)
		{
			int index = indices[i] + vertexOffset;
			auto &v = vertices[index];

			auto &texcoord = v.TextureCoordinates;
			auto &normal   = v.Normal;
			auto &position = v.Position;

			glTexCoord2fx12(texcoord.x, texcoord.y);
			// todo: inefficient, float and conversion from fx12 to float, and then to fx10
			glNormal3f((float)normal.x, (float)normal.y, (float)normal.z);
			glVertex3fx12(position.x, position.y, position.z);
		}

		glPopMatrix(1);
	}

	//-------------------------------------------------------------------------------------------------
	void GraphicsDevice::Clear( ClearOptions options, Color color/*, float depth, int stencil*/ )
	{
		sassert(IsMain(), "Error: The sub engine does not support 3D");

		if (options & ClearOptions::Target)
		{
			glClearColor(color.R(), color.G(), color.B(), 0); // BG must be opaque for AA to work
			glClearPolyID(63); // BG must have a unique polygon ID for AA to work
		}

		//if (options & ClearOptions::DepthBuffer)
		glClearDepth(GL_MAX_DEPTH);

		//if (options & ClearOptions::Stencil)
		// Todo: DS has a stencil buffer for shadow volumes
	}
}