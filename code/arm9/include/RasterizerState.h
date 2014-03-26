#pragma once

#include <nds/arm9/videoGL.h>

namespace Graphics
{
	// todo: check if clockwise is indeed back-facing!
	enum CullMode
	{
		None = POLY_CULL_NONE,
		CullClockwiseFace = POLY_CULL_BACK,
		CullCounterClockwiseFace = POLY_CULL_FRONT,
	};

	class RasterizerState
	{
	public:

		RasterizerState();

	public:

		Graphics::CullMode CullMode;
	};

	//-------------------------------------------------------------------------------------------------
	inline RasterizerState::RasterizerState()
	{
		CullMode = CullClockwiseFace;
	}
}