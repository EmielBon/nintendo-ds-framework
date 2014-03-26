#include "DisplayList.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "OpenGL.h"
#include "Assert.h"

namespace Graphics
{
	//-------------------------------------------------------------------------------------------------
	DisplayList::DisplayList(const VertexBuffer &vertexBuffer, const IndexBuffer &indexBuffer, const Texture &texture)
	{
		List<u8>  commands;
		List<u32> commandData;

		commands.push_back(FIFO_BEGIN);
		commandData.push_back(GL_TRIANGLES);

		for(int i = 0; i < indexBuffer.IndexCount(); ++i)
		{
			u16 index = indexBuffer[i];
			auto& v   = vertexBuffer[index];

			// Add texture coordinates
			commands.push_back(FIFO_TEX_COORD);

			fx4 tu = v.U * texture.Width;
			fx4 tv = v.V * texture.Height;
			commandData.push_back(TEXTURE_PACK(tof16(tu), tof16(tv)));

			// Add normal data
			commands.push_back(FIFO_NORMAL);
			commandData.push_back(v.Normal);

			// Add positional data
			commands.push_back(FIFO_VERTEX16);
			commandData.push_back(v.XY);
			commandData.push_back(v.Z);
		}

		// Synthesize the display list
		int dataCounter  = 0;
		int commandCount = commands.size();
		// First entry is the size of the display list
		int packedCommandCount = commands.size() / 4; // 1 display list entry per 4 packed commands
		packedCommandCount += (commands.size() % 4 == 0) ? 0 : 1; // If the last packed command is padded, add 1 more
		displayList.push_back(packedCommandCount + commandData.size());

		for(int i = 0; i < commandCount; i+=4)
		{
			int remaining = commandCount - i;
			u32 packedFifoCommand = 0;

			switch(remaining)
			{
			case 1:  packedFifoCommand = FIFO_COMMAND_PACK(commands[i],      FIFO_NOP,      FIFO_NOP,      FIFO_NOP); break;
			case 2:  packedFifoCommand = FIFO_COMMAND_PACK(commands[i], commands[i+1],      FIFO_NOP,      FIFO_NOP); break;
			case 3:  packedFifoCommand = FIFO_COMMAND_PACK(commands[i], commands[i+1], commands[i+2],      FIFO_NOP); break;
			default: packedFifoCommand = FIFO_COMMAND_PACK(commands[i], commands[i+1], commands[i+2], commands[i+3]); break;
			}
			
			displayList.push_back(packedFifoCommand);

			// Add the command data
			for(int j = 0; j < 4 && j < remaining; ++j)
			{
				u8 command = commands[i + j];

				switch(command)
				{
				case FIFO_TEX_COORD: displayList.push_back(commandData[dataCounter++]); break;
				case FIFO_NORMAL:    displayList.push_back(commandData[dataCounter++]); break;
				case FIFO_VERTEX16:  displayList.push_back(commandData[dataCounter++]);
					                 displayList.push_back(commandData[dataCounter++]); break;
				case FIFO_BEGIN:     displayList.push_back(commandData[dataCounter++]); break;
				default: CRASH("Invalid command specified in display list");            break;
				}
			}
		}

		ASSERT(displayList[0] == displayList.size() - 1, "Display list size does not packed command count + data size");
		ASSERT(displayList[2] == GL_TRIANGLES, "Something went wrong (1)");
		ASSERT(dataCounter == (int)commandData.size(), "Something went wrong (2)");
	}
}