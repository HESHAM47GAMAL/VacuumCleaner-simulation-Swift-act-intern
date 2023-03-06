#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "../Main/main.h"
typedef enum{
	MOTOR_ANGLE_10 =10,  /*angle for high speed*/
	MOTOR_ANGLE_90 =90 , /*angle for midum speed*/
	MOTOR_ANGLE_140 =140 /*angle for low speed*/
}tmotor_angle;

typedef enum
{
    MO_Switch,
		MO_Harmonic
}tMotor_STATE;

void Motor_Init(void);

void Motor_SetAngle(tmotor_angle angle_given);

void Motor_Update(void);

unsigned char Mo_Get_Actual_Angle(void);
void Mo_generate_firing_pulse(void);



#endif /*__MOTOR_H_*/
