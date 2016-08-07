#pragma once

#include "core/fixed.h"
#include "util/FixedHelper.h"
#include "util/Mat.h"
#include "graphics/GraphicsDevice.h"
#include "graphics/Texture.h"
#include <nds/arm9/videoGL.h>

template<int f>
static inline
int tof32(fixed<f> x)
{
	return Util::FixedHelper::Tof32(x);
}

template<int f>
static inline 
int tof16(fixed<f> x)
{
	return Util::FixedHelper::Tof16(x);
}

static inline
void glVertex3fx12(fx12 x, fx12 y, fx12 z)
{
	glVertex3v16(tof16(x), tof16(y), tof16(z));
}

static inline
void glTexCoord2fx12(fx12 u, fx12 v)
{
	// todo: use ActiveTexture only here and not in GraphicsDevice
	auto activeTexture = Graphics::GraphicsDevice::Main.ActiveTexture;

	if (activeTexture)
	{
		fx4 tu = u * activeTexture->Width;
		fx4 tv = v * activeTexture->Height;
		GFX_TEX_COORD = TEXTURE_PACK(tof16(tu), tof16(tv));
	}
}

static inline
void glScalefx12(fx12 x, fx12 y, fx12 z)
{
	glScalef32(tof32(x), tof32(y), tof32(z));
}

static inline
void glMultMatrixfx12(const Framework::Matrix &m) 
{
	MATRIX_MULT4x4 = tof32(m[ 0]);
	MATRIX_MULT4x4 = tof32(m[ 4]);
	MATRIX_MULT4x4 = tof32(m[ 8]);
	MATRIX_MULT4x4 = tof32(m[12]);

	MATRIX_MULT4x4 = tof32(m[ 1]);
	MATRIX_MULT4x4 = tof32(m[ 5]);
	MATRIX_MULT4x4 = tof32(m[ 9]);
	MATRIX_MULT4x4 = tof32(m[13]);

	MATRIX_MULT4x4 = tof32(m[ 2]);
	MATRIX_MULT4x4 = tof32(m[ 6]);
	MATRIX_MULT4x4 = tof32(m[10]);
	MATRIX_MULT4x4 = tof32(m[14]);

	MATRIX_MULT4x4 = tof32(m[ 3]);
	MATRIX_MULT4x4 = tof32(m[ 7]);
	MATRIX_MULT4x4 = tof32(m[11]);
	MATRIX_MULT4x4 = tof32(m[15]);
}