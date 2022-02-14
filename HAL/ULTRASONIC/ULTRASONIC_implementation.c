/*
 * ULTRASONIC_implementation.c
 *
 * Created: 2/12/2022 1:15:26 PM
 *  Author: No. 01
 */ 
#define F_CPU 8000000UL
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/DELAY/Delay.h"
#include "../../HAL/SW_ICU/SWICU_interface.h"
#include "ULTRASONIC_conf.h"
#include "ULTRASONIC_interface.h"
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
		SW_ICU_init();
		DIO_SETpinVal(ULTRASONIC_PORT,ULTRASONIC_ECHO,DIO_LOW);
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

// void ULTRASONIC_sendTrig()
// {
// 	DIO_SETpinVal(ULTRASONIC_PORT,ULTRASONIC_TRIGGER,DIO_HIGH);
// 	_delay_us(15);
// 	DIO_SETpinVal(ULTRASONIC_PORT,ULTRASONIC_TRIGGER,DIO_LOW);
// }
// 
// void ULTRASONIC_GetDis(unint16_t* u16_distance)
// {	
// 	uint32_t u32_numTicks;
// 	if(E_OK==SW_ICUCounts(&u32_numTicks))
// 	{
// 		*u16_distance=u32_numTicks/TICK_TO_CM_DIVISOR;
// 		//*u16_distance=u32_numTicks;
// 		return
// 	}
// 	else
// 	{
// 		return E_NOK;
// 	}
// }
 ERROR_STATUS_t ULTRASONIC_GetDis(unint16_t* u16_distance)
{
	uint32_t u32_numTicks; 
	if((!u8_trigFlag)&&(u8_delayFlag))
	{
		DIO_SETpinVal(ULTRASONIC_PORT,ULTRASONIC_TRIGGER,DIO_HIGH);
		_delay_us(20);
		DIO_SETpinVal(ULTRASONIC_PORT,ULTRASONIC_TRIGGER,DIO_LOW);	
		DELAY_start(60);
		u8_trigFlag=TRUE;
		u8_delayFlag=FALSE;
		u8_measuredFlag=FALSE;
		return E_NOK;
	}
	else if((!u8_delayFlag)&&(!u8_measuredFlag))
	{
		if(E_OK==SW_ICUCounts(&u32_numTicks))
		{
			//*u16_distance=u32_numTicks/TICK_TO_CM_DIVISOR;
			*u16_distance=u32_numTicks/58;
			u8_measuredFlag=TRUE;	
			return E_OK;
		}
		else
		{
			return E_NOK;
		}
	}
	else if((u8_trigFlag)&&(u8_measuredFlag))
	{
		if(E_OK==DELAY_isExpired())
		{
			u8_delayFlag=TRUE;
			u8_trigFlag=FALSE;
			return E_NOK;
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
// ERROR_STATUS_t ULTRASONIC_GetDis(unint16_t* u16_distance)
	// {
	// 	uint32_t u32_numTicks;
	// 	
	// 	DIO_SETpinVal(ULTRASONIC_PORT,ULTRASONIC_TRIGGER,DIO_HIGH);
	// 	_delay_us(15);
	// 	DIO_SETpinVal(ULTRASONIC_PORT,ULTRASONIC_TRIGGER,DIO_LOW);
	// 	