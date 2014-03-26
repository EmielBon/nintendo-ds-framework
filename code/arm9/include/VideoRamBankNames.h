#pragma once

#include "types.h"

namespace Graphics
{
	enum BankName
	{
		Bank0 = 0,
		BankA = BIT(0),
		BankB = BIT(1),  
		BankC = BIT(2), 
		BankD = BIT(3), 
		BankE = BIT(4), 
		BankF = BIT(5), 
		BankG = BIT(6), 
		BankH = BIT(7), 
		BankI = BIT(8),
		MainBanks = BankA | BankB | BankC | BankD,
		AuxBanks  = BankE | BankF | BankG | BankH | BankI,
		AllBanks  = MainBanks | AuxBanks,
	};
}