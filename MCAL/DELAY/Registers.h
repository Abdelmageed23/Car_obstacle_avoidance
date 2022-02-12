/*
 * Registers.h
 *
 * Created: 1/4/2022 7:19:53 PM
 *  Author: No. 01
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_


#define PORTA_DATA (*((volatile uint8_t *)(0x3B)))
#define PORTA_DIR (*((volatile uint8_t *)(0x3A)))
#define PORTA_STATUS (*((volatile uint8_t *)(0x39)))

#define PORTB_DATA (*((volatile uint8_t *)(0x38)))
#define PORTB_DIR (*((volatile uint8_t *)(0x37)))
#define PORTB_STATUS (*((volatile uint8_t *)(0x36)))

#define PORTC_DATA (*((volatile uint8_t *)(0x35)))
#define PORTC_DIR (*((volatile uint8_t *)(0x34)))
#define PORTC_STATUS (*((volatile uint8_t *)(0x33)))

#define PORTD_DATA (*((volatile uint8_t *)(0x32)))
#define PORTD_DIR (*((volatile uint8_t *)(0x31)))
#define PORTD_STATUS (*((volatile uint8_t *)(0x30)))


#define SREG (*((volatile uint8_t*)(0x5F)))
#define TIFR (*((volatile uint8_t*)(0x58)))
#define TIMSK (*((volatile uint8_t*)(0x59)))

#define TCCR0 (*((volatile uint8_t*)(0x53)))
#define TCNT0 (*((volatile uint8_t*)(0x52)))
#define OCR0 (*((volatile uint8_t*)(0x5C)))

#define TCCR2 (*((volatile uint8_t*)(0x45)))
#define TCNT2 (*((volatile uint8_t*)(0x44)))
#define OCR2 (*((volatile uint8_t*)(0x43)))

#endif /* REGISTERS_H_ */