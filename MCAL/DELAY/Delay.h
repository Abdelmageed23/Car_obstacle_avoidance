/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 8/1/2022            */
/* Version  : V01                 */
/**********************************/
#ifndef DELAY_H_
#define DELAY_H_

/*
typedef enum
{
    E_NOK,
    E_OK
}ERROR_STATUS_t;
*/

ERROR_STATUS_t DELAY_init(void);
ERROR_STATUS_t DELAY_start(unint16_t ms);
void DELAY_stop(void);
ERROR_STATUS_t DELAY_isExpired(void);

#endif
