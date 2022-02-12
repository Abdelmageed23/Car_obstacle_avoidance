#ifndef _TIMERS_INTERFACE_H_
#define _TIMERS_INTERFACE_H_

void Timer1_init(void);

void Timer1_start(void);

ERROR_STATUS_t Timer1_GetVal(unint16_t* u16_Time);

void TIMER1_CallBack(void (*TIMER_ISR)(void));

void Timer1_stop(void);

#endif
