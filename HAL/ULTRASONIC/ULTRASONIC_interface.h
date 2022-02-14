/*
 * ULTRASONIC_interface.h
 *
 * Created: 2/12/2022 1:15:04 PM
 *  Author: No. 01
 */ 


#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

ERROR_STATUS_t ULTRASONIC_init(void);
void ULTRASONIC_sendTrig();
ERROR_STATUS_t ULTRASONIC_GetDis(unint16_t* u16_distance);




#endif /* ULTRASONIC_INTERFACE_H_ */