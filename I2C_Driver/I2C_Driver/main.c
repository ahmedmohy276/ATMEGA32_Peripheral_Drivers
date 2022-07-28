/*
 * I2C_Driver.c
 *
 * Created: 10/31/2021 1:50:45 PM
 * Author : ahmed
 */ 

#define F_CPU 10000000

//#include <avr/io.h>
#include "STD_TYPES.h"
#include "I2C_CONFIG.h"
#include "I2C_INTERFACE.h"
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	TWI_VoidInit(PRESCALER_1,30,DISABLE_INT);
	//_delay_ms(50);
	TWI_VoidWriteByte(50,20,0X0A);

    while (1) 
    {
    }
}

