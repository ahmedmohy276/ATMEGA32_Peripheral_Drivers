/*
 * KEYPAD_DRIVER.c
 *
 * Created: 9/18/2021 3:10:43 PM
 * Author : ahmed
 */ 

//#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "DIO_INTERFACE.h"
#include "LCD_INTERFACE.h"
#include "KEYPAD_INTERFACE.h"
#include "KEYPAD_CONFIG.h"
#include "LCD_CONFIG.h"

int main(void)
{
	
    /* Replace with your application code */

	LCD_Void_4BitInit();
	Keypad_VoidInit();
	u8 x;
    while (1) 
    {
	
		x=Keypad_U8_GetPressed();
		LCD_Void_4BitSendChar(x);
	
    }
}

