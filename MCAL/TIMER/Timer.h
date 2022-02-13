/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 8/1/2022            */
/* Version  : V01                 */
/**********************************/
#ifndef TIMER_H_
#define TIMER_H_

ERROR_STATUS_t TIMER0_Init  (void);                          // initalize timer 0 configration
ERROR_STATUS_t TIMER0_Start(uint8_t intial_value);           // starts the timer with the intial required value
ERROR_STATUS_t TIMER0_Stop  (void);                          // stops the timer
ERROR_STATUS_t TIMER0_SetInitValue(uint8_t intial_value);    // function that sets the intial value
uint8_t TIMER0_u8OVFflag(void);                      // function to get the ovf flag
 
void SetCallBack_Timer0OVF(void(*func)(void));             // setting the callback function for OVF interrupt

#endif
