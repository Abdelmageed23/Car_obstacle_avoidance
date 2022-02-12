#ifndef _TIMER1_REGISTER_H_
#define _TIMER1_REGISTER_H_

#define TIMER1_TCCR1A	*((volatile uint8_t*)0x4F)
#define TCCR1A_WGM10	0
#define TCCR1A_WGM11	1
#define TCCR1A_FOC1B	2
#define TCCR1A_FOC1A	3
#define TCCR1A_COM1B0	4
#define TCCR1A_COM1B1	5
#define TCCR1A_COM1A0	6
#define TCCR1A_COM1A1	7

#define TIMER1_TCCR1B	*((volatile uint8_t*)0x4E)
#define TCCR1B_CS10		0
#define TCCR1B_CS11		1
#define TCCR1B_CS12		2
#define TCCR1B_WGM12	3
#define TCCR1B_WGM13	4
#define TCCR1B_ICES1	6
#define TCCR1B_ICNC1	7

#define TIMER1_TCNT		*((volatile unint16_t*)0x4C)

#define TIMER1_OCR1A	*((volatile unint16_t*)0x4A)
#define TIMER1_OCR1B	*((volatile unint16_t*)0x48)

#define TIMER1_ICR1		*((volatile unint16_t*)0x46)

#define TIMER1_TIFR		*((volatile uint8_t*)0x58)
#define TIFR_ICF1		5
#define TIFR_OCF1A		4
#define TIFR_OCF1B		3
#define TIFR_TOV1		2

#define TIMER1_TIMSK	*((volatile uint8_t*)0x59)
#define TIMSK_TICIE1	5
#define TIMSK_OCIE1A	4
#define TIMSK_OCIE1B	3
#define TIMSK_TOIE1		2


#endif
