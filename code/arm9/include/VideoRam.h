#pragma once

#include "types.h"
#include "VideoRamBank.h"

namespace Graphics
{
	class VideoRamBank;
	class MemorySlot;

	class VideoRam
	{
	public:
		
		// Initializes the Video RAM
		static void Initialize();

		/// Releases the bindings with MemorySlots of all VideoRamBanks and maps them to LCD
		static void Reset();

		///
		static VideoRamBank& GetBank(BankName name);

		///
		static VideoRamBank& GetBank(int index);

	public:

		static Array<VideoRamBank, 9> Banks;
	};
}