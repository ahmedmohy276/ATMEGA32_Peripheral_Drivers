/*
 * EXT_Interrupt.c
 *
 * Created: 9/25/2021 2:41:21 AM
 * Author : ahmed
 */ 


//#include <avr/io.h>
#define F_CPU 1000000

#include "DIO_INTERFACE.h"
#include "Interrupt_INTERFACE.h"
//#include <avr/interrupt.h>
#include <util/delay.h>

void myfunc(void);
void myfunc1(void);
void myfunc2(void);

int main(void)
{
    /* Replace with your application code */
	
	DIO_VoidSetPinDirection(2,portB,INPUT);
	DIO_VoidSetPinValue(2,portB,HIGH);
	
	DIO_VoidSetPinDirection(2,portD,INPUT);
	DIO_VoidSetPinValue(2,portD,HIGH);
	
	DIO_VoidSetPinDirection(3,portD,INPUT);
	DIO_VoidSetPinValue(3,portD,HIGH);
	
	Interrupt_VoidInterruptActivate(INT_0,FALLING_EDGE);
	Interrupt_VoidInterruptActivate(INT_1,FALLING_EDGE);
	Interrupt_VoidInterruptActivate(INT_2,FALLING_EDGE);
	
	DIO_VoidSetPinDirection(0,portC,OUTPUT);
	Interrupt_SetCallBackFunction(myfunc,INT_0);
	Interrupt_SetCallBackFunction(myfunc1,INT_1);
	Interrupt_SetCallBackFunction(myfunc2,INT_2);
    while (1) 
    {
		
    }
}

void myfunc(void)
{
	DIO_VoidSetPinValue(0,portC,HIGH);
	_delay_ms(1000);
	DIO_VoidSetPinValue(0,portC,LOW);
}

void myfunc1(void)
{
	DIO_VoidSetPinValue(0,portC,HIGH);
	_delay_ms(2000);
	DIO_VoidSetPinValue(0,portC,LOW);
}


void myfunc2(void)
{
	DIO_VoidSetPinValue(0,portC,HIGH);
	_delay_ms(3000);
	DIO_VoidSetPinValue(0,portC,LOW);
}

/*ISR(INT1_vect)
{
	DIO_VoidSetPinValue(0,portC,HIGH);
	_delay_ms(3000);
	DIO_VoidSetPinValue(0,portC,LOW);
}

ISR(INT2_vect)
{
	DIO_VoidSetPinValue(0,portC,HIGH);
	_delay_ms(3000);
	DIO_VoidSetPinValue(0,portC,LOW);
}*/

