#ifndef TIMER_H_
#define TIMER_H_

/*
typedef enum
{
    E_NOK,
    E_OK
}ERROR_STATUS_t;
*/

void DELAY_init(void);
ERROR_STATUS_t DELAY_start(uint16_t ms);
void DELAY_stop(void);
ERROR_STATUS_t DELAY_isExpired();




#endif
