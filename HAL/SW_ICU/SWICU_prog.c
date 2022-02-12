#include "STD_TYPES.h"

#include "EXTI_interface.h"
#include "SREG.h"
#include "TIMER1_interface.h"

#include "SWICU_private.h"
#include "SWICU_config.h"
#include "SWICU_interface.h"

unint16_t global_u16TimerCounts=0;
static uint8_t global_u8TimerFlags=0;
uint8_t global_u8ICUFlag=E_NOK;

static void TIMER1_ISR(void)
{
	global_u8TimerFlags++;
}

static void SW_ICU_ISR(void)
{
	static uint8_t local_u8Counter=0;
	local_u8Counter++;
	if(local_u8Counter == 1)
	{
		EXTI_EdgeTrig(INT2,FALLING);
		Timer1_start();
		TIMER1_CallBack(&TIMER1_ISR);
	}
	else if(local_u8Counter == 2)
	{
		Timer1_GetVal(&global_u16TimerCounts);
		Timer1_stop();
		local_u8Counter = 0;
		global_u8ICUFlag=E_OK;
	}
}

void SW_ICU_init(void)
{
	Timer1_init();
	SREG_Enable();
}

ERROR_STATUS_t SW_ICUCounts(uint32_t* u32_counts)
{
	EXTI_init(INT2);
	EXTI_CallBack(&SW_ICU_ISR);
	if(global_u8ICUFlag == E_OK)
	{
		u32_counts=(global_u8TimerFlags*TIMER1OV_counts)+global_u16TimerCounts;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
