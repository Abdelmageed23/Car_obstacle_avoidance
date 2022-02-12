/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 18/1/2022           */
/* Version  : V01                 */
/**********************************/
#ifndef LCD_H_
#define LCD_H_

#define LCD_MODULE_ID    (120U)   /* LCD Module Id                     */

/*
 * Macros for LCD DRIVER Status
 */
#define LCD_INITIALIZED                (1U)
#define LCD_NOT_INITIALIZED            (0U)

/******************************************************************************/
/*                          API Service Id Macros                             */
/******************************************************************************/

#define LCD_INIT_SID                    (uint8_t)0x00
#define LCD_WRITE_COMMAND_SID           (uint8_t)0x01
#define LCD_WRITE_DATA_SID              (uint8_t)0x02
#define LCD_WRITE_STRING_SID        	(uint8_t)0x03
#define LCD_WRITE_NUMBER_SID            (uint8_t)0x04
#define LCD_SET_POSTION_SID             (uint8_t)0x05
#define LCD_CLEAR_SID                   (uint8_t)0x06


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
ERROR_STATUS_t LCD_vidInit(void);
ERROR_STATUS_t LCD_vidWriteCommand(uint8_t command);
ERROR_STATUS_t LCD_vidWriteData(uint8_t data);
ERROR_STATUS_t LCD_vidWriteString(uint8_t*string);
ERROR_STATUS_t LCD_vidWriteNumber(uint32_t num);
ERROR_STATUS_t LCD_vidSetPosition(uint8_t row,uint8_t col);
ERROR_STATUS_t LCD_vidClear(void);

#endif /* LCD_H_ */
