#ifndef _TIMER2_REGISTER_H_
#define _TIMER2_REGISTER_H_

#define TIMERS_TCCR2	*((volatile char*)0x45)
#define TCCR2_CS20		0
#define TCCR2_CS21		1
#define TCCR2_CS22		2
#define TCCR2_WGM21		3
#define TCCR2_COM20		4
#define TCCR2_COM21		5
#define TCCR2_WGM20		6

#define TIMERS_TCNT2	*((volatile char*)0x44)

#define TIMERS_OCR2		*((volatile char*)0x43)

#define TIMERS_TIFR		*((volatile char*)0x58)
#define TIFR_TOV2		6
#define TIFR_OCF2		7

#define TIMERS_TIMSK	*((volatile char*)0x59)
#define TIMSK_TOIE2		6
#define TIMSK_OCIE2		7


#endif
