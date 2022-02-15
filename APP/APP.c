/*
 * Sprint6_COMM.c
 *
 * Created: 1/24/2022 8:04:48 PM
 * Author : No. 01
 */

#include "../LIB/STD_types.h"
#include "../MCAL/Interrupt/Interrupt_interface.h"
#include "../MCAL/DELAY/Delay.h"
#include "../HAL/MOTOR/Motor.h"
#include "../HAL/ULTRASONIC/ULTRASONIC_interface.h"
#include "../HAL/LCD/LCD.h"
#include "APP.h"
#include "APP_private.h"

ERROR_STATUS_t Robot_Init(void);
ERROR_STATUS_t Robot_Move(uint8_t Direction, uint8_t Speed);
ERROR_STATUS_t Robot_Stop(void);

uint8_t Delay_flag = E_NOK;
/*******************************************************************************
 *                     Function Implementation                                 *
 *******************************************************************************/
void APP_vidInit(void)
{
	/*Robot initialization*/
	Robot_Init();
	/*Ultrasonic initialization*/
	ULTRASONIC_init();
	/*global interrupt initialization*/
	GlobalInerruptEnable();
}
void APP_vidStart(void)
{
	unint16_t Object_Distance =INIT_byZero;//A local variable that holds the distance
	uint8_t state =State_A;

	while (1)
	{
		/*LCD initialization*/
		LCD_Init();

		/*go to the initial position*/
		LCD_SetPosition(X_init_POS,Y_init_POS);

		/*waiting until get reading*/
		while(ULTRASONIC_GetDis(&Object_Distance)!=E_OK);

		/*if the distance > 50 cm*/
		if(Object_Distance >= First_range)
		{
			/*Forward with high speed(80% of max speed)*/
			if(state != State_A)
			{
				if(Robot_Move(FORWARD,HIGH_SPEED))
				{
					LCD_WriteString("FORWARD");
					state = State_A;
					Delay_flag = E_OK;
				}
				else
				{
					Delay_flag = E_NOK;
				}
			}
		}
		/*if distance between 50 & 32*/
		else if(Object_Distance<First_range && Object_Distance >=Second_renge)
		{
			/*Forward with low speed (30% of max speed)*/
			if(state != State_B)
			{
				if(Robot_Move(FORWARD,LOW_SPEED))
				{
					LCD_WriteString("FORWARD");
					state = State_B;
					Delay_flag=E_OK;
				}
				else
				{
					Delay_flag = E_NOK;
				}
			}
		}
		/*if distance between 32 & 28 cm*/
		else if(Object_Distance<Second_renge && Object_Distance >=Third_range)
		{
			/*Turn right*/
			if(Robot_Move(RIGHT,LOW_SPEED))
			{
				LCD_WriteString("RIGHT");
				state = State_C;
				Delay_flag = E_OK;
			}
			else
			{
				Delay_flag = E_NOK;
			}
		}
		/*if distance < 28 cm*/
		else if (Object_Distance<=Third_range)
		{
			/*Backward*/
			if(state != State_D)
			{
				if(Robot_Move(BACKWORD,LOW_SPEED))
				{
					LCD_WriteString("BACKWARD");
					state = State_D;
					Delay_flag=E_OK;
				}
				else
				{
					Delay_flag=E_NOK;
				}
			}
		}
		if(Delay_flag == E_OK)
		{
			/*Display the distance on LCD*/
			LCD_SetPosition(X_SEC_POS,Y_init_POS);
			LCD_WriteString("    ");
			LCD_SetPosition(X_SEC_POS,Y_init_POS);
			LCD_WriteNumber(Object_Distance);
		}
		else
		{/*do nothing*/}
	}
}

/*******************************************************************************
 *                     Private Function Implementation                         *
 *******************************************************************************/
/* Robot Driver */
static uint8_t Robot_Initialized =E_NOK;
ERROR_STATUS_t Robot_Init()
{
	/*delay initialization (Timer1)*/
	DELAY_init();
	/*Motor 1 initialization*/
	MOTOR_init(MOTOR_1);
	/*Motor 2 initialization*/
	MOTOR_init(MOTOR_2);
	Robot_Initialized =E_OK;
	return E_OK;
}


ERROR_STATUS_t Robot_Move(uint8_t Direction, uint8_t Speed)
{
	/*Check if the initialization has finished or not*/
	if(Robot_Initialized != E_OK)
	{
		/*if not finished return not OK*/
		return E_NOK;
	}
	/*if finished*/
	else
	{
		/*select action depends on direction*/
		switch (Direction)
		{
		/*Direction forward*/
		case FORWARD:
			MOTOR_speed(Speed);
			MOTOR_direction(MOTOR_1, FWD);
			MOTOR_direction(MOTOR_2, FWD);
			break;
			/*Direction backword*/
		case BACKWORD:
			MOTOR_speed(Speed);
			MOTOR_direction(MOTOR_1, REV);
			MOTOR_direction(MOTOR_2, REV);
			break;
			/*Direction right*/
		case RIGHT:
			MOTOR_speed(MID_SPEED);
			MOTOR_direction(MOTOR_1, FWD);
			MOTOR_direction(MOTOR_2, REV);
			DELAY_start(600);
			if(E_OK ==DELAY_isExpired())
			{
				Robot_Stop();
			}
			else
			{
				return E_NOK;
			}
			break;
			/*Direction left*/
		case LEFT:
			MOTOR_speed(MID_SPEED);
			MOTOR_direction(MOTOR_1, REV);
			MOTOR_direction(MOTOR_2, FWD);
			DELAY_start(600);
			if(E_OK ==DELAY_isExpired())
			{
				Robot_Stop();
			}
			else
			{
				return E_NOK;
			}
			break;
		default:
			return E_NOK;
		}

		return E_OK;
	}
}

/*Robot stop*/
ERROR_STATUS_t Robot_Stop()
{
	if(Robot_Initialized != E_OK)
	{
		return E_NOK;
	}
	else
	{
		/*Motor 1 OFF*/
		MOTOR_off(MOTOR_1);
		/*Motor 2 OFF*/
		MOTOR_off(MOTOR_2);
		return E_OK;
	}
}
