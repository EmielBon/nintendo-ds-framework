#pragma once

#include "IGraphicsResource.h"
#include "types.h"
#include <nds/arm9/sprite.h>

namespace LLR
{
	struct SpriteResource : public IGraphicsResource
	{
	public:

		SpriteResource() = default;

		int ByteSize() const;

	public:

		List<SpriteEntry> OAMSpriteEntries;
	};

	//-------------------------------------------------------------------------------------------------
	int SpriteResource::ByteSize() const
	{
		return OAMSpriteEntries.size() * sizeof(SpriteEntry);
	}
}