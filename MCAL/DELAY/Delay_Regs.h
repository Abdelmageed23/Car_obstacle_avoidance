/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 8/1/2022            */
/* Version  : V01                 */
/**********************************/

#ifndef DELAY_REGS_H_
#define DELAY_REGS_H_

#define TIMSK *((volatile uint8_t *)0x59)
#define TCCR1A *((volatile uint8_t *)0x4F)
#define TCCR1B *((volatile uint8_t *)0x4E)
#define ICR1 *((volatile unint16_t *)0x46)
#define OCR1 *((volatile unint16_t *)0x4A)
#define TIFR *((volatile uint8_t *)0x58)

#endif /* DELAY_REGS_H_ */