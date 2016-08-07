#include "graphics/BasicEffect.h"

#include "graphics/GraphicsDevice.h"
#include "graphics/TextureMemory.h"
#include "graphics/OpenGL.h"
#include "util/StringHelper.h"
#include "debug/Profiler.h"

namespace Graphics
{
	using namespace Framework;

	BasicEffect::BasicEffect()
	{
		Alpha = 1.0f;
		AmbientLightColor = Color::Black;
		DiffuseColor = Color::White;
		DirectionalLight0 = DirectionalLight(0, POLY_FORMAT_LIGHT0, Color::White);
		DirectionalLight1 = DirectionalLight(1, POLY_FORMAT_LIGHT1, Color::White);
		DirectionalLight2 = DirectionalLight(2, POLY_FORMAT_LIGHT2, Color::White);
		DirectionalLight3 = DirectionalLight(3, POLY_FORMAT_LIGHT3, Color::White);
		EmissiveColor = Color::Black;
		FogColor = Color::White;
		FogEnabled = false;
		FogStart = 100.0f;
		FogEnd = 100.0f;
		LightingEnabled = false;
		Projection = Matrix::Identity();
		SpecularColor = Color::Black;
		SpecularPower = 1.0f;
		TextureEnabled = true;
		VertexColorEnabled = false;
		View = Matrix::Identity();
		World = Matrix::Identity();
	}

	//-------------------------------------------------------------------------------------------------
	void BasicEffect::Apply()
	{
		PROFILE_METHOD(FXAply);

		glMaterialf(GL_EMISSION, EmissiveColor);
		glMaterialf(GL_AMBIENT, AmbientLightColor);
		glMaterialf(GL_DIFFUSE, DiffuseColor);

		u32 lightStatus = 0;

		if (LightingEnabled) 
		{
			Array<DirectionalLight*, 4> lights = {{ &DirectionalLight0, &DirectionalLight1, &DirectionalLight2, &DirectionalLight3 }};

			for(u32 i = 0; i < lights.size(); ++i)
			{
				DirectionalLight& light = *lights[i];
				lightStatus |= (light.Enabled) ? light.StatusBit : 0;
				SynchronizeLight(light);
			}
		}
		
		if (TextureEnabled)
		{
			GraphicsDevice::Main.TextureMemory->AddTexture(Texture);
			GraphicsDevice::Main.ActiveTexture = Texture;
			
			int textureWidth  = TextureSizeParameter(Texture->Width);
			int textureHeight = TextureSizeParameter(Texture->Height);
			u16* addr = GraphicsDevice::Main.TextureMemory->GetTextureAddress(Texture);
			GFX_TEX_FORMAT = (textureWidth << 20) | (textureHeight << 23) | (1 << 16) | (1 << 17) | (GL_RGBA << 26) | (( (uint32)addr >> 3 ) & 0xFFFF);
		}
		else
		{
			//glDisable(GL_TEXTURE_2D);
		}

		ASSERT(Alpha >= 0 && Alpha <= 1, "Error: Invalid Alpha value");

		int alpha = (int)(Alpha * 31);
		glPolyFmt(POLY_ALPHA(alpha) | GraphicsDevice::Main.RasterizerState.CullMode | lightStatus);
		
		PROFILE_METHOD(FXMatr);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMultMatrixfx12(Projection);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glPushMatrix();
		
		glMultMatrixfx12(View);
		
		// Scaling, has to be separate from the world transformation to keep light vectors intact
		Ptr<Vector3> scale = New<Vector3>();
		World.Decompose(scale, nullptr, nullptr);

		// Do the rest of the world transformation
		Matrix worldNoScale = World.RemoveScaling(*scale);
		glMultMatrixfx12(worldNoScale);
		
		glScalefx12(scale->x, scale->y, scale->z);

		auto &viewPort = GraphicsDevice::Main.ViewPort;
		glViewport(viewPort.X, viewPort.Y, viewPort.Width, viewPort.Height);
	}

	//-------------------------------------------------------------------------------------------------
	int BasicEffect::TextureSizeParameter( int size )
	{
		switch(size)
		{
		case    8: return TEXTURE_SIZE_8;
		case   16: return TEXTURE_SIZE_16;
		case   32: return TEXTURE_SIZE_32;
		case   64: return TEXTURE_SIZE_64;
		case  128: return TEXTURE_SIZE_128;
		case  256: return TEXTURE_SIZE_256;
		case  512: return TEXTURE_SIZE_512;
		case 1024: return TEXTURE_SIZE_1024;
		default: CRASH("Unsupported texture size: " << size);
		}
		return 0;
	}

	//-------------------------------------------------------------------------------------------------
	void BasicEffect::SynchronizeLight( const DirectionalLight &light )
	{
		// todo: inefficient, conversion from fx12 to float, then to fx10
		glLight(light.Id, light.DiffuseColor, floattov10((float)light.Direction.x), floattov10((float)light.Direction.y), floattov10((float)light.Direction.z));
	}
}