/*
 * Sprint6_COMM.c
 *
 * Created: 1/24/2022 8:04:48 PM
 * Author : No. 01
 */

#include "../LIB/STD_types.h"
#include "../MCAL/Interrupt/Interrupt_interface.h"
#include "../HAL/MOTOR/Motor.h"
#include "APP.h"
#include "APP_private.h"
/*******************************************************************************
 *                     Function Implementation                                 *
 *******************************************************************************/
void APP_vidInit(void)
{
	Robot_Init();
	LCD_vidInit();
	Ultrasonic_init();
	GlobalInerruptEnable();							////////////////////////////////////////////
}
void APP_vidStart(void)
{
	unint16_t Object_Distance =0;
	while (1)
	{
		/* code */
		UltrasonicGetDis(&Object_Distance);
		if(Object_Distance >= 50)
		{
			Robot_Move(FORWARD,80);
			LCD_vidWriteString("FORWARD");
		}
		else if(Object_Distance<50 && Object_Distance >=32)
		{
			Robot_Move(FORWARD,30);
			LCD_vidWriteString("FORWARD");
		}
		else if(Object_Distance<32 && Object_Distance >=28)
			{
				Robot_Move(RIGHT,30);
				LCD_vidWriteString("RIGHT");
			}
		else if (Object_Distance<=28)
		{
			Robot_Move(BACKWORD,30);
			LCD_vidWriteString("BACKWORD");
		}
		LCD_vidSetPosition(1,4);
		LCD_vidWriteNumber(Object_Distance);
	}
	
}

/*******************************************************************************
 *                     Private Function Implementation                         *
 *******************************************************************************/













/* Robot Driver */
static uint8_t Robot_Initialized =0;
ERROR_STATUS_t Robot_Init()
{

	DELAY_init();
	MOTOR_init(MOTOR_1);
	MOTOR_init(MOTOR_2);
	Robot_Initialized =1;
	return E_OK;
}


ERROR_STATUS_t Robot_Move(uint8_t Direction, uint8_t Speed)
{
	if(Robot_Initialized != 1)
	{
		return E_NOK;
	}
	else
	{
		switch (Direction)
		{
		case FORWARD:
			 MOTOR_speed(Speed);
			 MOTOR_direction(MOTOR_1, FWD);
			 MOTOR_direction(MOTOR_2, FWD);
			 break;
		case BACKWORD:
			 MOTOR_speed(Speed);
			 MOTOR_direction(MOTOR_1, REV);
			 MOTOR_direction(MOTOR_2, REV);
			 break;
		case RIGHT:
			 MOTOR_speed(Speed);
			 MOTOR_direction(MOTOR_1, FWD);
			 MOTOR_direction(MOTOR_2, REV);
			 DELAY_start(300);					/////////////////////////////////// needed
			 while(E_OK !=DELAY_isExpired());
			 Robot_Stop();
			 break;
		case LEFT:
			 MOTOR_speed(Speed);
			 MOTOR_direction(MOTOR_1, REV);
			 MOTOR_direction(MOTOR_2, FWD);
			 DELAY_start(300);					/////////////////////////////////// needed
			 while(E_OK !=DELAY_isExpired());
			 Robot_Stop();
			 break;
		default:
			return E_NOK;
		}

		return E_OK;
	}
}


ERROR_STATUS_t Robot_Stop()
{
	if(Robot_Initialized != 1)
		{
			return E_NOK;
		}
		else
		{
			MOTOR_off(MOTOR_1);
			MOTOR_off(MOTOR_2);
			return E_OK;
		}
}
