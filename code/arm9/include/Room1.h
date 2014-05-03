#pragma once

#include "types.h"
#include "Room.h"
#include "Link.h"

namespace Test
{
	class Room1 : public Framework2D::Room
	{
	private:
			
		using base = Framework2D::Room;

	public:

		void Initialize();
		
		void Update(const GameTime &gameTime);

	public:

		Ptr<Link> link;
	};

}