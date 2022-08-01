/*
 * DIO_Driver.c
 *
 * Created: 9/14/2021 2:24:19 AM
 * Author : ahmed
 */ 

//#include <avr/io.h>
#define  F_CPU 1000000
#include <util/delay.h>
#include "DIO_INTERFACE.h"

int main(void)
{

    /* Replace with your application code */
	DIO_VoidSetPinDirection(0,portD,OUTPUT);
	DIO_VoidSetPinDirection(4,portA,INPUT);
	DIO_VoidSetPinValue(4,portA,HIGH);     //activate pull up resistor at pin A4

	DIO_VoidSetPortDirection(portC,OUTPUT);
	DIO_VoidSetPortValue(portC,HIGH);
	
    while (1) 
    {
		if (((DIO_U8GetPinValue(4,portA)) & (0X01)) == 0)
		{
			DIO_VoidSetPinValue(0,portD,HIGH);
			_delay_ms(500);
			DIO_VoidSetPinValue(0,portD,LOW);
			_delay_ms(500);
		} 
    }
}

