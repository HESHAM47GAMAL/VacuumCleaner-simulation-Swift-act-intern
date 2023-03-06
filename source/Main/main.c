#include "../Main/main.h"
#include "../Modules/SW.h"
#include "../Modules/Timer.h"
#include "../Modules/Display.h"
#include "../Modules/Led.h"
#include "../Modules/VC.h"
#include "../Modules/Motor.h"
#include "stdio.h"

///Oscilloscope should monitor C6 and C7 channels


volatile unsigned char ISR_FLAG;  /*to tell me that 100ms finished (should be 10ms but I explain in video)*/

int main(void)
{
    /* Initialization */
   
   printf("Vacuum Cleaner is starting ...\n");
   
    SW_Init();
    DISP_Init();
    VC_Init();
    Motor_Init();

    //Initialize the timer and start it
    TMR_Init();
    TMR_Start();

    while (1)
    {
			if(ISR_FLAG == 1)
			{
					
				Motor_Update();
				
				ISR_FLAG =0;
			}
			VC_Update();
			SW_Update();
			DISP_Update();
			
			
			
				
			
      // Sleep
     //__WFI();
    }

    return 0;
}

