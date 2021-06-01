
#include "stdio.h"
#include "DriverJeuLaser.h"
#include "GestionSon.h"
#include "Affichage_Valise.h"

extern int DFT_ModuleAuCarre( short int * Signal64ech, char k) ;
extern short int LeSignal[];
extern int LongueurSon;
extern int PeriodeSonMicroSec;


int Resu[64];
short int dma_buf[64];

int counter[4] = {0,0,0,0};
int pointcounter[4] = {0,0,0,0};


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
	counter[0]++;
	counter[1]++;
	counter[2]++;
	counter[3]++;//Compteur de temps incrementer toute les 5 ms
		
}


int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================

	// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
	InitSon();
	CLOCK_Configure();

	Systick_Period_ff(360000);
	Systick_Prio_IT( 0, callback );
  SysTick_On;
	SysTick_Enable_IT;
	
	Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, dma_buf );
	
	Timer_1234_Init_ff(TIM4,72*PeriodeSonMicroSec);
	PWM_Init_ff(TIM3, 3, 720);
	Active_IT_Debordement_Timer( TIM4, 2, CallbackSon);	
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	
	Init_Affichage();
	
	
		

	//============================================================================	


		
	while	(1)
		{
			Prepare_Afficheur(1, pointcounter[0]);
			Prepare_Afficheur(2, pointcounter[1]);
			Prepare_Afficheur(3, pointcounter[2]);
			Prepare_Afficheur(4, pointcounter[3]);
			Prepare_Set_LED(LED_LCD_R);
			Mise_A_Jour_Afficheurs_LED();
			
			if(Resu[17]>300000 && counter[0] > 21){ //85000 KHz
				
				counter[0] = 0;
				if(pointcounter[0] < 99){pointcounter[0]++;}
				StartSon();
				
			}
			
			if(Resu[19]>300000 && counter[1] > 21){ //95000 KHz
				
				counter[1] = 0;
				if(pointcounter[1] < 99){pointcounter[1]++;}
				StartSon();
				
			}
			
			if(Resu[23]>300000 && counter[2] > 21){ //115000 KHz
				
				counter[2] = 0;
				if(pointcounter[2] < 99){pointcounter[2]++;}
				StartSon();
				
			}
			
			if(Resu[24]>300000 && counter[3] > 21){ //120000 KHz
				
				counter[3] = 0;
				if(pointcounter[3] < 99){pointcounter[3]++;}
				StartSon();
				
			}
			
		}
}

