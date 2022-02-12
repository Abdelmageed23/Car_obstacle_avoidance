/**********************************/
/* Author   : Abdalla Abdelhafiz  */
/* Date     : 18/1/2022           */
/* Version  : V01                 */
/**********************************/
#include "../../01-LIB/01-STD_TYPES/STD_TYPES.h"
#include "../../01-LIB/02-BIT_MATH/BIT_MATH.h"
#include "../../01-LIB/03-DET/Det.h"
#include "../../02-MCAL/DIO/Dio.h"
#include <util/delay.h>
#include "LCD_cfg.h"
#include "LCD.h"

#define STATE_A 0
#define STATE_B 1

static uint8_t LCD_Status = LCD_NOT_INITIALIZED;
static uint8_t LCD_init_state = STATE_A;


// ********* FUNCTIONS IMPLMENTATION **********

// function to intialize the LCD with the configured pins
ERROR_STATUS_t LCD_vidInit(void)
{
	if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		uint8_t expired;
		if (LCD_init_state == STATE_A)
		{
			// setting the pins direction
			DIO_SETpinDir(LCD_Port, LCD_RS, OUTPUT);
			DIO_SETpinDir(LCD_Port, LCD_RW, OUTPUT);
			DIO_SETpinDir(LCD_Port, LCD_E, OUTPUT);
			DIO_SETpinDir(LCD_Port, LCD_D4, OUTPUT);
			DIO_SETpinDir(LCD_Port, LCD_D5, OUTPUT);
			DIO_SETpinDir(LCD_Port, LCD_D6, OUTPUT);
			DIO_SETpinDir(LCD_Port, LCD_D7, OUTPUT);
			if (DELAY_start(50) == E_NOK)
			{
				return E_NOK;
			}
			LCD_init_state = STATE_B;
			return E_OK;
		}
		else if (LCD_init_state == STATE_B)
		{
			DELAY_isExpired(&expired);
			if (expired == TRUE)
			{
				DIO_vidSetPinValue(LCD_Port, LCD_RS, 0);
				DIO_vidSetPinValue(LCD_Port, LCD_RW, 0);
				DIO_vidSetPinValue(LCD_Port, LCD_D4, 0);
				DIO_vidSetPinValue(LCD_Port, LCD_D5, 1);
				DIO_vidSetPinValue(LCD_Port, LCD_D6, 0);
				DIO_vidSetPinValue(LCD_Port, LCD_D7, 0);
				DIO_vidSetPinValue(LCD_Port, LCD_E, STD_HIGH);
				_delay_us(250);
				DIO_vidSetPinValue(LCD_Port, LCD_E, STD_LOW);

				_delay_us(500);
				LCD_Status = LCD_INITIALIZED;

				LCD_vidWriteCommand(0b00101000);
				_delay_us(250);
				LCD_vidWriteCommand(0b00001100);
				_delay_us(250);
				LCD_vidWriteCommand(0b00000001);
				_delay_us(250);
			}
			else
			{
				return E_OK;
			}
		}
		else
		{
			return E_NOK;
		}
	}
	else
	{
		return E_NOK;
	}
}

// function to send a command to LCD
ERROR_STATUS_t LCD_vidWriteCommand(uint8_t command)
{
	if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_WRITE_COMMAND_SID);
		return E_NOK;
	}
	else
	{
		DIO_SETpinVal(LCD_Port, LCD_RS, 0);
		DIO_SETpinVal(LCD_Port, LCD_RW, 0);
		DIO_SETpinVal(LCD_Port, LCD_D4, GET_BIT(command, 4));
		DIO_SETpinVal(LCD_Port, LCD_D5, GET_BIT(command, 5));
		DIO_SETpinVal(LCD_Port, LCD_D6, GET_BIT(command, 6));
		DIO_SETpinVal(LCD_Port, LCD_D7, GET_BIT(command, 7));

		DIO_SETpinVal(LCD_Port, LCD_E, STD_HIGH);
		_delay_us(250);
		DIO_SETpinVal(LCD_Port, LCD_E, STD_LOW);

		DIO_SETpinVal(LCD_Port, LCD_RS, 0);
		DIO_SETpinVal(LCD_Port, LCD_RW, 0);
		DIO_SETpinVal(LCD_Port, LCD_D4, GET_BIT(command, 0));
		DIO_SETpinVal(LCD_Port, LCD_D5, GET_BIT(command, 1));
		DIO_SETpinVal(LCD_Port, LCD_D6, GET_BIT(command, 2));
		DIO_SETpinVal(LCD_Port, LCD_D7, GET_BIT(command, 3));

		DIO_SETpinVal(LCD_Port, LCD_E, STD_HIGH);
		_delay_us(250);
		DIO_SETpinVal(LCD_Port, LCD_E, STD_LOW);
		_delay_us(250);

		return E_OK;
	}
}

// function that writes  one element on the LCD
ERROR_STATUS_t LCD_vidWriteData(uint8_t data)
{
	if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_WRITE_DATA_SID);
		return E_NOK;
	}
	else
	{
		DIO_SETpinVal(LCD_Port, LCD_RS, 1);
		DIO_SETpinVal(LCD_Port, LCD_RW, 0);
		DIO_SETpinVal(LCD_Port, LCD_D4, GET_BIT(data, 4));
		DIO_SETpinVal(LCD_Port, LCD_D5, GET_BIT(data, 5));
		DIO_SETpinVal(LCD_Port, LCD_D6, GET_BIT(data, 6));
		DIO_SETpinVal(LCD_Port, LCD_D7, GET_BIT(data, 7));

		DIO_SETpinVal(LCD_Port, LCD_E, STD_HIGH);
		_delay_us(250);
		DIO_SETpinVal(LCD_Port, LCD_E, STD_LOW);

		DIO_SETpinVal(LCD_Port, LCD_RS, 1);
		DIO_SETpinVal(LCD_Port, LCD_RW, 0);
		DIO_SETpinVal(LCD_Port, LCD_D4, GET_BIT(data, 0));
		DIO_SETpinVal(LCD_Port, LCD_D5, GET_BIT(data, 1));
		DIO_SETpinVal(LCD_Port, LCD_D6, GET_BIT(data, 2));
		DIO_SETpinVal(LCD_Port, LCD_D7, GET_BIT(data, 3));

		DIO_SETpinVal(LCD_Port, LCD_E, STD_HIGH);
		_delay_us(250);
		DIO_SETpinVal(LCD_Port, LCD_E, STD_LOW);
		_delay_us(250);

		return E_OK;
	}
}
// function to write string on the LCD
ERROR_STATUS_t LCD_vidWriteString(uint8_t *string)
{
	if (string == NULL_PTR)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_WRITE_STRING_SID);
		return E_NOK;
	}
	else if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_WRITE_STRING_SID);
		return E_NOK;
	}
	else
	{
		uint8_t index = 0;
		while (string[index] != 0)
		{
			LCD_vidWriteData(string[index]);
			index++;
		}
		return E_OK;
	}
}

// function to write a number on the LCD
ERROR_STATUS_t LCD_vidWriteNumber(uint32_t num)
{
	if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_WRITE_NUMBER_SID);
		return E_NOK;
	}
	else
	{
		uint32_t reversed = 1;
		if (num == 0)
		{
			LCD_vidWriteData('0');
		}
		else
		{
			while (num != 0)
			{
				reversed = (reversed * 10) + (num % 10);
				num /= 10;
			}
			while (reversed != 1)
			{
				LCD_vidWriteData(((reversed % 10) + '0'));
				reversed /= 10;
			}
		}
		return E_OK;
	}
}

// function that sets the postion that u want to write in
ERROR_STATUS_t LCD_vidSetPosition(uint8_t row, uint8_t col)
{
	if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_SET_POSTION_SID);
		return E_NOK;
	}
	else
	{
		uint8_t adrs = 128;
		switch (row)
		{
		case 0:
			adrs += col;
			break;
		case 1:
			adrs += (64 + col);
			break;
		}
		LCD_vidWriteCommand(adrs);
		return E_OK;
	}
}

// function to clear the LCD
ERROR_STATUS_t LCD_vidClear(void)
{
	if (LCD_Status == LCD_NOT_INITIALIZED)
	{
		Det_ReportError(LCD_MODULE_ID, LCD_CLEAR_SID);
		return E_NOK;
	}
	else
	{
		LCD_vidWriteCommand(0b00000001);
		_delay_us(500);
		return E_OK;
	}
}
