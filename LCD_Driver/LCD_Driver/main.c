/*
 * LCD_Driver.c
 *
 * Created: 9/16/2021 5:18:42 PM
 * Author : ahmed
 */ 

#define F_CPU 16000000

//#include <avr/io.h>
#include <util/delay.h>
#include "DIO_INTERFACE.h"
#include "LCD_INTERFACE.h"
#include "LCD_CONFIG.h"
#include "STD_TYPES.h"


int main(void)
{
    /* Replace with your application code */
	
	LCD_Void_4BitInit();
	u64 num =123456789;
	u8 z=70;
    while (1) 
    {
		LCD_Void_4BitSendCommand(DISPLAYCLEAR);
		LCD_Void_4BitSendString((u8*)"X=");
		LCD_Void_4BitSendNumber(num);
		_delay_ms(1000);
		LCD_Void_4BitSendCommand(DISPLAYCLEAR);
		LCD_Void_4BitSendString((u8*)"Helloooo");
		_delay_ms(1000);
		LCD_Void_4BitSendCommand(DISPLAYCLEAR);
		LCD_Void_4BitSendString((u8*)"Y=");
		LCD_Void_4BitSendNumber(123456);
		_delay_ms(1000);
		LCD_Void_4BitSendCommand(DISPLAYCLEAR);
		LCD_Void_4BitSendString((u8*)"welcome");
		_delay_ms(1000);


    }
}

