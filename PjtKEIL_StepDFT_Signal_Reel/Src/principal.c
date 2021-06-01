
#include "stdio.h"
#include "DriverJeuLaser.h"
//#include "GestionSon.h"
extern int DFT_ModuleAuCarre( short int * Signal64ech, char k) ;
extern short int LeSignal[];
//extern int LongueurSon;
//extern int PeriodeSonMicroSec;


int Resu[64];
short int dma_buf[64];

void callback()
{
	
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	// Les 64 echantillons sont deja en RAM
	for (int k=0;k<64;k++)
		{
			Resu[k]=DFT_ModuleAuCarre(dma_buf,k);
		}
}


int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================

	// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
	CLOCK_Configure();

	Systick_Period_ff(360000);
	Systick_Prio_IT( 0, callback );
  SysTick_On;
	SysTick_Enable_IT;
	
	Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, dma_buf );
	
	//Timer_1234_Init_ff(TIM4,72*PeriodeSonMicroSec);
	//PWM_Init_ff(TIM3, 3, 720);
	//Active_IT_Debordement_Timer( TIM4, 2, CallbackSon);	
	//GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	
		//StartSon();

	//============================================================================	


		
	while	(1)
		{
			//if(Resu[17]
		}
}

