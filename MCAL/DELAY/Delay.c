/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 8/1/2022            */
/* Version  : V01                 */
/**********************************/
#include "../../LIB/STD_TYPES.h"
#include "Registers.h"
#include "Delay.h"

#define __INTR_ATTRS used, externally_visible

#define WGM20 6
#define WGM21 3
#define CS22 2
#define CS21 1
#define CS20 0

#define GLOBAL_INTERRUPT_ENABLE 7

#define TOIE2 6

#define HIGH 1 
#define LOW 0

#define TRUE 1
#define FALSE 0

#define NUM_TICKS_PER_MS 1000


// global variable to count the number of overflows
volatile uint32_t gu32_flagCounter = 0;
uint32_t gu32_maxFlags;
uint8_t gu8_initialTicks=0;
uint8_t gu8_doneFlag = FALSE;
uint8_t gu8_busyFlag = FALSE;


//yehia
void DELAY_init(void)
{
	//all normal operation with normal mode, no clock selected
	TCCR2 = LOW;
    // enable Timer 2 Overflow interrupt
    TIMSK=(HIGH<<TOIE2);
	SREG|=(HIGH<<GLOBAL_INTERRUPT_ENABLE);
}
//yehia
ERROR_STATUS_t DELAY_start(unint16_t ms)
{
	uint32_t u32_totalTicks;
	
        if(TRUE==gu8_busyFlag){
            return E_NOK;
        }
		else
		{
			u32_totalTicks=ms*NUM_TICKS_PER_MS;
			gu8_initialTicks=u32_totalTicks%256;
			gu32_maxFlags = u32_totalTicks/256;
			gu8_busyFlag = TRUE;
			gu8_doneFlag = FALSE;
			TCNT2=gu8_initialTicks;
			// set up timer with prescaler = 8
			TCCR2|=(HIGH<<CS21);
			return E_OK;
		}
}
//yehia
inline void DELAY_stop(void)
{
	TCCR2 &= ~((HIGH<<CS22)|(HIGH<<CS21)|(HIGH<<CS20)); // clock disable
    gu8_busyFlag = FALSE;   
}
//yehia
ERROR_STATUS_t DELAY_isExpired()
{

	if(TRUE==gu8_doneFlag)
	{
		gu8_doneFlag=FALSE;
		return E_OK;
	}
   else
   {
	   return E_NOK;
   }
}

// TIMER2 OVF ISR
void __vector_5(void) __attribute__((signal, __INTR_ATTRS));
void __vector_5(void)
{
	if(gu32_maxFlags!=0)
	{
		PORTA_DIR=0xFF;
		PORTA_DATA=0x0F;
		gu32_flagCounter++;
		if (gu32_flagCounter == gu32_maxFlags)
		{
			PORTA_DATA=0xF0;
			gu8_doneFlag = TRUE;
			gu32_flagCounter = 0;
			//gu8_busyFlag = FALSE;
			DELAY_stop();
		}
	}
}
