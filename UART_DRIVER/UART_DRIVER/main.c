/*
 * UART_TX_WITH_LCD.c
 *
 * Created: 10/6/2021 2:40:19 AM
 * Author : ahmed
 */ 

#define F_CPU 2000000

//#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "DIO_INT.h"
#include "LCD_INTERFACE.h"
#include "LCD_INTERFACE.h"
#include "UART_CONFIG.h"
#include "UART_INTERFACE.h"
#include "UART_REGISTERS.h"

int main(void)
{
	
	
    /* Replace with your application code */
	DIO_init(0, D, uint8_t direction)
	DIO_init(1,D,OUT);
	
	UART_VoidInit();
	
	UART_VoidParityBit(EVEN_PARITY);
	
	UART_VoidSetMode(ASYNCH_NORMAL_MODE);
	
	UART_VoidSeCharSize(CHAR_SIZE_8);
	
	UART_VoidSetBaudeRate(9600,ASYNCH_NORMAL_MODE,FOSC);
	
	UART_VoidStopBit(STOP_BIT_2);
	
	UART_VoidSetSYNCHModeCLKPolarity(RISING_FALLING);
	
	UART_VoidTXINTEnable(TX_ENABLE);
	void UART_VoidRXINTEnable(RX_ENABLE);
	
	u8 data=7;
	u8 arr_data[] ={1,2,4,8,15,'\0'};
	
	_delay_ms(100);
	/************************************************************************/
	/*                      Synchronous functions test                      */
	/************************************************************************/
	//UART_VoidSYNCHSendChar(data);
	//UART_VoidSYNCHSendString(arr_data);
	UART_VoidSYNCHSendString("Hello");
	
	/*UART_VoidSYNCHSendChar(data);
	_delay_ms(50);
	UART_VoidSYNCHSendChar(data+1);
	_delay_ms(50);
	UART_VoidSYNCHSendChar(32);
	_delay_ms(50);
	UART_VoidSYNCHSendString("Hello");
	_delay_ms(500);
	UART_VoidSYNCHSendChar(32);
	_delay_ms(50);
	UART_VoidSYNCHSendChar(data);
	_delay_ms(50);
	UART_VoidSYNCHSendChar(data+1);*/
	
	/************************************************************************/
	/*                     ASynchronous functions test                      */
	/************************************************************************/
	
	//UART_VoidASYNCHSendChar(data);
	//UART_VoidASYNCHSendString(arr_data);
	//UART_VoidASYNCHSendString("Hello");
	
	/*UART_VoidASYNCHSendChar(data);
	_delay_ms(50);
	UART_VoidASYNCHSendChar(data+1);
	_delay_ms(50);
	UART_VoidASYNCHSendChar(32);
	_delay_ms(50);
	UART_VoidASYNCHSendString("Hello");
	_delay_ms(500);
	UART_VoidASYNCHSendChar(32);
	_delay_ms(50);
	UART_VoidASYNCHSendChar(data);
	_delay_ms(50);
	UART_VoidASYNCHSendChar(data+1);*/

	
    while (1) 
    {
		
    }
}

