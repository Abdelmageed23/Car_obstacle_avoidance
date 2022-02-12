#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/EXTI/EXTI_interface.h"
#include "../../MCAL/TIMER1/TIMER1_interface.h"

#include "SWICU_private.h"
#include "SWICU_config.h"
#include "SWICU_interface.h"

unint16_t global_u16TimerCounts=Initial_zero;
static uint8_t global_u8TimerFlags=Initial_zero;
uint8_t global_u8ICUFlag=E_NOK;

static void TIMER1_ISR(void)
{
	global_u8TimerFlags++;
}

static void SW_ICU_ISR(void)
{
	static uint8_t local_u8Counter=Initial_zero;
	local_u8Counter++;
	if(local_u8Counter == FirstRound)
	{
		Timer1_start();
		TIMER1_CallBack(&TIMER1_ISR);
		EXTI_EdgeTrig(INT2,FALLING);
	}
	else if(local_u8Counter == SecondRound)
	{
		Timer1_GetVal(&global_u16TimerCounts);
		Timer1_stop();
		local_u8Counter = Initial_zero;
		global_u8ICUFlag=E_OK;
	}
}

void SW_ICU_init(void)
{
	Timer1_init();
}

ERROR_STATUS_t SW_ICUCounts(uint32_t* u32_counts)
{
	EXTI_init(INT2);
	EXTI_CallBack(&SW_ICU_ISR);
	if(global_u8ICUFlag == E_OK)
	{
		u32_counts=(global_u8TimerFlags*TIMER1OV_counts)+global_u16TimerCounts;
		global_u8TimerFlags = Initial_zero;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
