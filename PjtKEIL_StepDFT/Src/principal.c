

#include "DriverJeuLaser.h"

extern int DFT_ModuleAuCarre( short int * Signal64ech, char k) ;
extern short int LeSignal[];
int Resu[64];

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();


	
	

//============================================================================	

for (int k=1;k<64;k++)
		{
			Resu[k]=DFT_ModuleAuCarre(LeSignal,k);
		}
	
while	(1)
	{

	}
}

