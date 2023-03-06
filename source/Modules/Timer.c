#include "../Main/main.h"
#include "../Modules/Timer.h"
#include "../Modules/SW.h"
//#include "../Modules/Time.h"
#include "../Modules/Display.h"
#include "../Modules/Led.h"
#include "../Modules/Motor.h"
#include "stm32f4xx_ll_tim.h"
#include "../Modules/VC.h"
#include "stdio.h"

// For debugging only (For logic analyzer)
volatile uint32_t tick = 0;


/*as we start with 170 degree and 1 degree take 500us = systick_handler*/
unsigned char counter_for_degree = 170 ;  /* 1 degree = 10 ms / 180 = 55us*/

unsigned char count_to_100ms = 0 ; /*counter to tell me number of count to make 100ms*/

extern volatile unsigned char ISR_FLAG;

void TMR_Init(void)
{
   // System clock frequency = 16MHz
   
	 SysTick_Config(16*TMR_TICK_MS*37); //*take  500 us *//
   TMR_Stop();
}
void TMR_Start(void)
{
   SysTick->CTRL |= (0x03);
}

void TMR_Stop(void)
{
   SysTick->CTRL &= ~(0x03);
}

void SysTick_Handler(void)
{
	
	count_to_100ms ++ ;
	
	if(count_to_100ms == counter_for_degree)
	{
		Mo_generate_firing_pulse(); /*fire at specific time */
	}
	
	if(count_to_100ms  == 200)
	{
		// For debugging only (For logic analyzer)
   tick ^= 1;
		
	 counter_for_degree = Mo_Get_Actual_Angle(); /*here get actual angle to know correct time to fire*/
		
		ISR_FLAG = 1;
	
   
   // Do nothing
   // It is made only to wake the cpu up

		
		count_to_100ms =0; /*reset count*/
	}
   
}

