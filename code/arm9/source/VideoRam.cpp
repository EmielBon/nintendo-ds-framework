#include "VideoRam.h"

#include "Debug.h"
#include "VideoRamBank.h"
#include <nds\arm9\video.h>

namespace Graphics
{
	Array<VideoRamBank, 9> VideoRam::Banks;

	//-------------------------------------------------------------------------------------------------
	void VideoRam::Initialize()
	{
		int kb = 1024;

		Banks[0] = VideoRamBank(BankA, &VRAM_A_CR, VRAM_A, 128*kb);
		Banks[1] = VideoRamBank(BankB, &VRAM_B_CR, VRAM_B, 128*kb);
		Banks[2] = VideoRamBank(BankC, &VRAM_C_CR, VRAM_C, 128*kb);
		Banks[3] = VideoRamBank(BankD, &VRAM_D_CR, VRAM_D, 128*kb);
		Banks[4] = VideoRamBank(BankE, &VRAM_E_CR, VRAM_E,  64*kb);
		Banks[5] = VideoRamBank(BankF, &VRAM_F_CR, VRAM_F,  16*kb);
		Banks[6] = VideoRamBank(BankG, &VRAM_G_CR, VRAM_G,  16*kb);
		Banks[7] = VideoRamBank(BankH, &VRAM_H_CR, VRAM_H,  32*kb);
		Banks[8] = VideoRamBank(BankI, &VRAM_I_CR, VRAM_I,  16*kb);
	}

	//-------------------------------------------------------------------------------------------------
	void VideoRam::Reset()
	{
		for(u32 i = 0; i < Banks.size(); ++i)
			Banks[i].Release();
	}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"

	//-------------------------------------------------------------------------------------------------
	VideoRamBank& VideoRam::GetBank(BankName name)
	{
		for(u32 i = 0; i < Banks.size(); ++i)
			if (Banks[i].GetName() == name)
				return Banks[i];

		ASSERT(false, "Error: Invalid bank name specified");
	}

#pragma GCC diagnostic pop

	//-------------------------------------------------------------------------------------------------
	VideoRamBank& VideoRam::GetBank(int index)
	{
		ASSERT(index >= 0 && (u32)index < Banks.size(), "Error: VRAM Bank index out of range");
		return Banks[index];
	}

}