#ifndef APP_H_
#define APP_H_



void APP_vidInit(void);
void APP_vidStart(void);


ERROR_STATUS_t Robot_Init();
ERROR_STATUS_t Robot_Move(uint8_t Direction, uint8_t Speed);
ERROR_STATUS_t Robot_Stop();

#define FORWARD 1
#define BACKWORD 2
#define RIGHT	3
#define LEFT 4

#endif
