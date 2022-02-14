#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TIMER2_register.h"
#include "TIMER2_private.h"
#include "TIMER2_config.h"
#include "TIMER2_interface.h"

#define T2_EMPTY 0

void (*CALL_BACK_T2)(void);

void Timer2_init(void)
{
	/*Normal Mode*/
#if MODE2 == NORMAL
	/*Normal Mode*/
	CLR_BIT(TIMERS_TCCR2,TCCR2_WGM20);
	CLR_BIT(TIMERS_TCCR2,TCCR2_WGM21);
#elif MODE2 == PWM_PHASE_CORRECT
	/*Phase Correct Mode*/
	SET_BIT(TIMERS_TCCR2,TCCR2_WGM20);
	CLR_BIT(TIMERS_TCCR2,TCCR2_WGM21);
#elif MODE2 == CTC
	/*CTC Mode*/
	CLR_BIT(TIMERS_TCCR2,TCCR2_WGM20);
	SET_BIT(TIMERS_TCCR2,TCCR2_WGM21);
#elif MODE2 == PWM_FAST
	/*Fast PWM Mode*/
	SET_BIT(TIMERS_TCCR2,TCCR2_WGM20);
	SET_BIT(TIMERS_TCCR2,TCCR2_WGM21);
#endif
}

void Timer2_start(void)
{
	TIMERS_TCNT2=T2_EMPTY;
	/*Prescalar Select*/
#if PRESCALAR2 == DIV_1
	/*select No prescaler*/
	SET_BIT(TIMERS_TCCR2,TCCR2_CS20);
	CLR_BIT(TIMERS_TCCR2,TCCR2_CS21);
	CLR_BIT(TIMERS_TCCR2,TCCR2_CS22);
#elif PRESCALAR2 == DIV_8
	/*select prescaler (Divide by 8)*/
	CLR_BIT(TIMERS_TCCR2,TCCR2_CS20);
	SET_BIT(TIMERS_TCCR2,TCCR2_CS21);
	CLR_BIT(TIMERS_TCCR2,TCCR2_CS22);
#elif PRESCALAR2 == DIV_32
	/*select prescaler (Divide by 32)*/
	SET_BIT(TIMERS_TCCR2,TCCR2_CS20);
	SET_BIT(TIMERS_TCCR2,TCCR2_CS21);
	CLR_BIT(TIMERS_TCCR2,TCCR2_CS22);
#elif PRESCALAR2 == DIV_64
	/*select prescaler (Divide by 64)*/
	CLR_BIT(TIMERS_TCCR2,TCCR2_CS20);
	CLR_BIT(TIMERS_TCCR2,TCCR2_CS21);
	SET_BIT(TIMERS_TCCR2,TCCR2_CS22);
#elif PRESCALAR2 == DIV_128
	/*select prescaler (Divide by 128)*/
	SET_BIT(TIMERS_TCCR2,TCCR2_CS20);
	CLR_BIT(TIMERS_TCCR2,TCCR2_CS21);
	SET_BIT(TIMERS_TCCR2,TCCR2_CS22);
#elif PRESCALAR2 == DIV_256
	/*select prescaler (Divide by 256)*/
	CLR_BIT(TIMERS_TCCR2,TCCR2_CS20);
	SET_BIT(TIMERS_TCCR2,TCCR2_CS21);
	SET_BIT(TIMERS_TCCR2,TCCR2_CS22);
#elif PRESCALAR2 == DIV_1024
	/*select prescaler (Divide by 1024)*/
	SET_BIT(TIMERS_TCCR2,TCCR2_CS20);
	SET_BIT(TIMERS_TCCR2,TCCR2_CS21);
	SET_BIT(TIMERS_TCCR2,TCCR2_CS22);
#endif

	/*Timer overflow interrupt Enable*/
	/*If select normal mode*/
	if(MODE2==NORMAL)
	{
		SET_BIT(TIMERS_TIMSK,TIMSK_TOIE2);
	}
	/*If select ctc mode*/
	else if(MODE2== CTC)
	{
		SET_BIT(TIMERS_TIMSK,TIMSK_OCIE2);
	}
}

ERROR_STATUS_t Timer2_GetVal(uint8_t* u8_Time)
{
	if(u8_Time != NULL)
	{
		*u8_Time=TIMERS_TCNT2;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

void Timer2_stop(void)
{
	/*Clear PRESCALAR to Stop timer*/
	CLR_BIT(TIMERS_TCCR2,TCCR2_CS20);
	CLR_BIT(TIMERS_TCCR2,TCCR2_CS21);
	CLR_BIT(TIMERS_TCCR2,TCCR2_CS22);

	/*Timer overflow interrupt Disable*/
	/*If select normal mode*/
	if(MODE2==NORMAL)
	{
		CLR_BIT(TIMERS_TIMSK,TIMSK_TOIE2);
	}
	/*If select ctc mode*/
	else if(MODE2== CTC)
	{
		CLR_BIT(TIMERS_TIMSK,TIMSK_OCIE2);
	}
}

void TIMER2_clear(void)
{
	TIMERS_TCNT2=T2_EMPTY;
}
void TIMER2_CallBack(void (*TIMER_ISR)(void))
{
	CALL_BACK_T2 = TIMER_ISR;
}

void __vector_5(void)	__attribute__((signal));
void __vector_5(void)
{
	if(CALL_BACK_T2 != NULL)
	{
		CALL_BACK_T2();
	}
}
