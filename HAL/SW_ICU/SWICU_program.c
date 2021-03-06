#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/EXTI/EXTI_interface.h"
#include "../../MCAL/TIMER2/TIMER2_interface.h"
#include "SWICU_private.h"
#include "SWICU_config.h"
#include "SWICU_interface.h"

typedef enum 
{
	STATE_initial,
	STATE_rising,
	STATE_falling
	}EN_EXTI_state_t;

uint8_t global_u8TimerCounts=Initial_zero;
uint32_t global_u32TimerFlags=Initial_zero;
uint8_t global_u8ICUFlag=E_NOK;
static EN_EXTI_state_t global_EN_EXTI_state=STATE_initial;

/*a local function that counts the over flows*/
static void TIMER2_ISR(void)
{
	/*Increase number or flags that counts overflow*/
	global_u32TimerFlags++;

}

/*ISR when external interrupt happens in rising edge*/
void SW_ICU_RISING(void)
{
	global_EN_EXTI_state=STATE_rising;
	Timer2_start();
	EXTI_EdgeTrig(INT2,FALLING);
	EXTI_CallBack(SW_ICU_FALLING);
}

/*ISR when external interrupt happens in falling edge*/
 void SW_ICU_FALLING(void)
{
	global_EN_EXTI_state=STATE_falling;
	Timer2_stop();
	EXTI_EdgeTrig(INT2,RISING);
	EXTI_CallBack(SW_ICU_RISING);
}

 /*initialization of timer 2, external interrupt and call back functions*/
void SW_ICU_init(void)
{
	Timer2_init();
	TIMER2_CallBack(TIMER2_ISR);
	EXTI_init(INT2);
	EXTI_CallBack(SW_ICU_RISING);
}

/*A function that calculate the counts*/
ERROR_STATUS_t SW_ICUCounts(uint32_t* u32_counts)
{
	switch(global_EN_EXTI_state)
	{
		case STATE_rising : 
		return E_NOK;
		
		case STATE_falling :
		Timer2_GetVal(&global_u8TimerCounts);
		if(global_u32TimerFlags>120)
		{
			global_u32TimerFlags=Initial_zero;
		}
		*u32_counts=((global_u32TimerFlags*TIMER2OV_counts)+global_u8TimerCounts);

		global_u32TimerFlags=Initial_zero;
		return E_OK;
		
		default: return E_NOK;
	}
}
