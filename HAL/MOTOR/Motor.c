/*
 * Motor.c
 *
 * Created: 1/9/2022 5:56:57 PM
 *  Author: No. 01
 */ 
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../HAL/PWM/PWM.h"
#include "MOTOR_CONFIG.h"
#include "Motor.h"



ERROR_STATUS_t MOTOR_init(uint8_t numMotor)// numMotor (initialize Direction pins only (PWM initializes enable pins inside them))
{
	if(MOTOR_1==numMotor)
	{
		if((E_OK==DIO_SETpinDir(MOTOR_PORT,MOTOR_DIR_1A,DIO_OUTPUT))&&(E_OK==DIO_SETpinDir(MOTOR_PORT,MOTOR_DIR_1B,DIO_OUTPUT)))
		{
			return PWM_Init();			
		}
		else
		{
			return E_NOK;
		}
	}
	else if(MOTOR_2==numMotor)
	{
		if((E_OK==DIO_SETpinDir(MOTOR_PORT,MOTOR_DIR_2A,DIO_OUTPUT))&&(E_OK==DIO_SETpinDir(MOTOR_PORT,MOTOR_DIR_2B,DIO_OUTPUT)))
		{
			return PWM_Init();
		}
		else
		{
			return E_NOK;
		}
	}
	else
	{
		return E_NOK;
	}
}

ERROR_STATUS_t MOTOR_speed(uint8_t dutyCycle)//  30/60/90 (Start PWM and initialize duty cycle)
{
	return PWM_SetDutyCycle(dutyCycle);
}
ERROR_STATUS_t MOTOR_direction(uint8_t numMotor, uint8_t DIR)//  numMotor/(FWD,REV) (Set direction of specified motor) i.e (MOTOR_1, FWD) meaning motor 1, move forward
{
	if(MOTOR_1==numMotor)
	{
		if(FWD==DIR)
		{
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_1A,DIO_HIGH);
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_1B,DIO_LOW);
			return E_OK;
		}
		else if(REV==DIR)
		{
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_1A,DIO_LOW);
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_1B,DIO_HIGH);
			return E_OK;	
		}
		else
		{
			return E_NOK;
		}
	}
	else if(MOTOR_2==numMotor)
	{
		if(FWD==DIR)
		{
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_2A,DIO_HIGH);
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_2B,DIO_LOW);
			return E_OK;
		}
		else if(REV==DIR)
		{
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_2A,DIO_LOW);
			DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_2B,DIO_HIGH);
			return E_OK;
		}
		else
		{
			return E_NOK;
		}
	}
	else
	{
		return E_NOK;
	}
	
	
}
ERROR_STATUS_t MOTOR_off(uint8_t numMotor)// stop specified motor (writes LOW on DIR data pins)
{
	if(MOTOR_1==numMotor)
	{
		DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_1A,DIO_LOW);
		DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_1B,DIO_LOW);
		return E_OK;
	}
	else if(MOTOR_2==numMotor)
	{
		DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_2A,DIO_LOW);
		DIO_SETpinVal(MOTOR_PORT,MOTOR_DIR_2B,DIO_LOW);
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
