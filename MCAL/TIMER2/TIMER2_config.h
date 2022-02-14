#ifndef _TIMER2_CONFIG_H_
#define _TIMER2_CONFIG_H_


/*Select a TIMER Mode:
						1-NORMAL
						2-PWM_PHASE_CORRECT
						3-CTC
						4-PWM_FAST*/
#define MODE2			NORMAL


/*Select the prescalar:
 	 	 	 	 	 	 1-DIV_1
 	 	 	 	 	 	 2-DIV_8
 	 	 	 	 	 	 3-DIV_32 //For TIMER2 only.
 	 	 	 	 	 	 4-DIV_64
 	 	 	 	 	 	 5-DIV_128 //For timer2 only.
 	 	 	 	 	 	 6-DIV_256
 	 	 	 	 	 	 7-DIV_1024
 	 	 	 	 	 	 */

#define PRESCALAR2		DIV_8



#endif
