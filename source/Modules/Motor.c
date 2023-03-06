#include "../Main/main.h"
#include "../Modules/Motor.h"
#include "../Port/Port.h"
#include "stm32f4xx_ll_gpio.h"
#include "../Modules/Timer.h"
#include "stdio.h"

volatile uint32_t fire = 0;

#define FIRING_PULSE_WIDTH (100)

/* TIME BETWEEN TWO INVOKATION TO UPDATE FUNCTION*/
#define MOTOR_UPDATE_TICK (20)

/* initial value of the angle */
#define INITIAL_ANGLE (170)

/* kruz number to reduce the harmonics*/
#define KRUZ_CONST (10)

/* Time between adding 1 degree to the actual speed
 * on switching mode to achieve soft starting  
 */
#define SWITCHING_TIME (40)

/* count the number of ms elapsed between two addition process to actual angle in soft switching mode*/
static unsigned int soft_switching_counter;

/* static variable speed target*/
 tmotor_angle target_angle; 
/* static variable actual firing angle*/
 unsigned char actual_angle;

/* static variable for motor state*/
volatile  tMotor_STATE motor_state;
/*counter to count in update function */
static unsigned char  motor_tick_counter =0;

void Motor_Init(void)
{
	/*enable clock source for motor*/
	MOTOR_ENABLE_CLOCK;
	
	/*init port for pin */
	LL_GPIO_InitTypeDef Motor_GPIO;
	Motor_GPIO.Pin = MOTOR_PIN;
	Motor_GPIO.Mode = LL_GPIO_MODE_OUTPUT;
	Motor_GPIO.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	Motor_GPIO.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	Motor_GPIO.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	Motor_GPIO.Pull = LL_GPIO_PULL_NO;
	Motor_GPIO.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(MOTOR_PORT,&Motor_GPIO); /*pass variable that contain all seting parameter to init this pin*/
	/*angle that I will start when power on */
	actual_angle = INITIAL_ANGLE;
	/*angle I target to go on after power on to make vacuum work with mid speed*/
	target_angle = MOTOR_ANGLE_90;
	/*set motor state that is softswitch to to move from 170 to 90 angle*/
	motor_state = MO_Switch;
	// reset the switching counter
	soft_switching_counter = 0;
}

void Motor_SetAngle(tmotor_angle angle_given)
{
	
	// if speed == target speed
    if(target_angle == angle_given)return;
    /* true return*/  
	/*false
     * change mode to switching
     * set speed in target speed 
     */
    motor_state = MO_Switch;
    target_angle = angle_given;
}


void Motor_Update(void)
{
	
	/* increment motor tick counter*/
	motor_tick_counter += TMR_TICK_MS;
	if ( motor_tick_counter != MOTOR_UPDATE_TICK)/* check condition that make me apply update function every 20ms*/
		return ;
	/*reset count*/
	
	
	motor_tick_counter = 0 ;
	/*state machine handle*/
	switch (motor_state)
	{
		case MO_Harmonic:
			/*here we apply Harmonic Reduction */
			/*as every time enter function reduce 5 and encrease 5 of actaul value to get average*/
			/*here increase 10 on actual value*/
			if(target_angle > actual_angle)
				actual_angle += 10;
			/*here decrease 10 on actual value*/
			else if(target_angle < actual_angle)
				actual_angle -= 10;
			break;
			
		case MO_Switch:
			/*here get target value and  set actual value to be suitable for Harmonic Reduction */
			if(target_angle == actual_angle)
			{
				actual_angle -= 5;/*here reduce 5 as when enter Harmonic Reduction  mode will inrease and decrease 10  (Ex 90 angle --> 85)--> 95 :85 -->average = 90*/
				/*here we get target speed and will switch to mode Harmonic Reduction  */
				motor_state = MO_Harmonic;
			}
			else 
			{
				/*here we increase time */
				soft_switching_counter += MOTOR_UPDATE_TICK ; 
				/*check if get time to apply soft switching */
				if(soft_switching_counter == SWITCHING_TIME)
				{
					/*here try to make actual to catch target */
					if(target_angle > actual_angle)
						actual_angle ++ ;
					else if(target_angle < actual_angle)
						actual_angle -- ;
					/*clear counter to be able to go on soft switch mode */
					soft_switching_counter = 0;
				}
			}
			
		
			break;
		default :
			/*nothing to do */
			break;
		
	}
}


unsigned char Mo_Get_Actual_Angle(void)
{
	
	return actual_angle;
}


void Mo_generate_firing_pulse(void)
{
	// set motor pin high
	LL_GPIO_SetOutputPin(MOTOR_PORT,MOTOR_PIN);
	fire = 1;
	// delay for 100 us
	volatile int count = (33 * 12) / 4;
	for (int i = 0; i < count; ++i) 
	{
			count--;
	}
	// reset motor pin
	LL_GPIO_ResetOutputPin(MOTOR_PORT,MOTOR_PIN);
	fire = 0;
}