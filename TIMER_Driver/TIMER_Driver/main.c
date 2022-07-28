/*
 * TIMER_Driver.c
 *
 * Created: 9/28/2021 4:47:37 PM
 * Author : ahmed
 */ 

#define F_CPU 8000000

//#include <avr/io.h>

#include "TIMER_INTERFACE.h"
#include "STD_TYPES.h"
#include "DIO_INTERFACE.h"
#include <util/delay.h>


void myfunc(void);
void myfunc2(void);

int main(void)
{
    /* Replace with your application code */
	DIO_VoidSetPinDirection(0,portD,OUTPUT);
	DIO_VoidSetPinDirection(1,portD,OUTPUT);
	
	/*DIO_VoidSetPinValue(0,portD,HIGH);
	delay_ms(1000);
	DIO_VoidSetPinValue(0,portD,LOW);
	Timer_VoidSetAlarm(4000,TIMER_2,myfunc);*/
	Timer_VoidPWMGeneration(TIMER_2,90,FAST_PWM_MODE,NON_INVERTING_MODE,NO_PRESCALER);
	Timer_VoidPWMGeneration(TIMER_0,60,PWM_PHASE_CORRECT_MODE,NON_INVERTING_MODE,NO_PRESCALER);
    while (1) 
    {
		/*DIO_VoidSetPinValue(0,portD,HIGH);
		delay_ms(1000);
		DIO_VoidSetPinValue(0,portD,LOW);
		delay_ms(1000);*/
    }
}

void myfunc(void)
{
	DIO_VoidSetPinValue(1,portD,HIGH);
}

void myfunc2(void)
{
	DIO_VoidSetPinValue(0,portD,LOW);
}
