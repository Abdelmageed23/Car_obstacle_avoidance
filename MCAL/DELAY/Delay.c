/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 8/1/2022            */
/* Version  : V01                 */
/**********************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "Delay_Regs.h"
#include "Delay.h"

// global variable to count the number of overflows
volatile unint16_t tot_overflow_T1 = 0;
static unint16_t max_ovf_T1;
static uint8_t T1_done = FALSE;
static uint8_t T1_busy = FALSE;

ERROR_STATUS_t DELAY_init(void)
{
	TCCR1A = 0;
	// ctc mode
	TCCR1B = (1 << 3);
	// compare value
	OCR1 = 1000;    // number of ticks that happens in 1 ms
	// enable compA interrupt
	SET_BIT(TIMSK, 4);
	return E_OK;
}

ERROR_STATUS_t DELAY_start(unint16_t ms)
{
	if (T1_busy == TRUE)
	{
		return E_NOK;
	}
	tot_overflow_T1 = 0;
	max_ovf_T1 = ms;
	T1_busy = TRUE;
	T1_done = FALSE;
	// set up timer with prescaler = 8
	SET_BIT(TCCR1B, 1);

	return E_OK;
}

inline void DELAY_stop(void)
{
	TCCR1B &= ~(0b111); // clock disable
	T1_busy = FALSE;
}

ERROR_STATUS_t DELAY_isExpired(void)
{
	if (T1_done == TRUE)
	{
		return E_OK;
	}
	else
	{
		return NOK;
	}
}

// TIMER1 compA ISR
void __vector_7(void) __attribute__((signal, __INTR_ATTRS));
void __vector_7(void)
{
	tot_overflow_T1++;
	if (tot_overflow_T1 == max_ovf_T1)
	{
		T1_done = TRUE;
		T1_busy = FALSE;
		DELAY_stop();
	}
	else
	{
		T1_done = FALSE;
	}
}
