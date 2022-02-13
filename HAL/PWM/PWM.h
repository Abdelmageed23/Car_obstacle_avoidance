/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     :10/1/2022            */
/* Version  : V01                 */
/**********************************/
#ifndef PWM_H_
#define PWM_H_


ERROR_STATUS_t PWM_Init(void);                 // call this function to intialize the driver before starting the pwm
ERROR_STATUS_t PWM_SetDutyCycle(uint8_t dutyc);  // setting the duty cycle you can call it anytime after starting the pwm generation to modify the dutycycle

#endif
