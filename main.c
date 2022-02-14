#include "LIB/STD_TYPES.h"
#include "APP/APP.h"
#include "HAL/LCD/LCD.h"
#include "HAL/ULTRASONIC/ULTRASONIC_interface.h"
#include "MCAL/DELAY/Delay.h"
#include "MCAL/Interrupt/Interrupt_interface.h"
#include "util/delay.h"


int main()
{
    APP_vidInit();
    APP_vidStart();

    return 0;

}

/*
void main()
{
	DELAY_init();
	GlobalInerruptEnable();
	ULTRASONIC_init();
	uint8_t x=0;
		while(1)
			{
				LCD_Init();
				if(ULTRASONIC_GetDis(&x)==E_OK)
				{
					LCD_SetPosition(1,0);
					LCD_WriteString("          ");
					LCD_SetPosition(1,0);
					LCD_WriteNumber(x);

				}
				_delay_ms(500);
//				LCD_SetPosition(1,0);
//				LCD_WriteNumber(23);
				//LCD_WriteString("HHHHHHHHHH");
			}
}

*/

