#ifndef _TIMER2_INTERFACE_H_
#define _TIMER2_INTERFACE_H_

void Timer2_init(void);

void Timer2_start(void);

ERROR_STATUS_t Timer2_GetVal(uint8_t* u8_Time);

void TIMER2_CallBack(void (*TIMER_ISR)(void));

void Timer2_stop(void);

#endif
