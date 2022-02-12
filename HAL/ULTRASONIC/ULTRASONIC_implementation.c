/*
 * ULTRASONIC_implementation.c
 *
 * Created: 2/12/2022 1:15:26 PM
 *  Author: No. 01
 */ 
#define F_CPU 8000000UL
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include<util/delay.h>

static uint8_t u8_trigFlag=FALSE;
static uint8_t u8_delayFlag=TRUE;
static uint8_t u8_measuredFlag=FALSE;

//calculated by the following equation: 1 / ( TIME FOR 1 TICK * speed of sound in CM/SEC / 2) 
#define TICK_TO_CM_DIVISOR 466 

ERROR_STATUS_t ULTRASONIC_init(void)
{
	if((E_OK==DIO_SETpinDir(ULTRASONIC_PORT,ULTRASONIC_TRIGGER,DIO_OUTPUT))&&(E_OK==DIO_SETpinDir(ULTRASONIC_PORT,ULTRASONIC_ECHO,DIO_INPUT)))
	{
		//SW_ICU_init();
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}


ERROR_STATUS_t ULTRASONIC_GetDis(unint16_t* u16_distance)
{
	unint16_t u32_numTicks; 
	if((!u8_trigFlag)&&(u8_delayFlag))
	{
		DIO_SETpinVal(ULTRASONIC_PORT,ULTRASONIC_TRIGGER,DIO_HIGH);
		_delay_us(15);
		DIO_SETpinVal(ULTRASONIC_PORT,ULTRASONIC_TRIGGER,DIO_LOW);	
		//DELAY_ms(60);
		u8_trigFlag=TRUE;
		u8_delayFlag=FALSE;
		u8_measuredFlag=FALSE;
		return E_NOK;
	}
	else if((!u8_delayFlag)&&(!u8_measuredFlag))
	{
		if(//E_OK==ICU_getcounts(&u32_numTicks))
		{
			*u16_distance=u32_numTicks/TICK_TO_CM_DIVISOR;
			u8_measuredFlag=TRUE;	
			return E_OK;
		}
	}
	else if((u8_trigFlag)&&(u8_measuredFlag))
	{
		if(//E_OK==isExpired())
		{
			u8_delayFlag=TRUE;
			u8_trigFlag=FALSE;
			return E_NOK;
		}
	}
	else
	{
		return E_NOK;
	}
	
}