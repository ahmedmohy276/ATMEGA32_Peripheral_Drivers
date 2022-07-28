/*
 * DIO_PROG.c
 *
 * Created: 9/14/2021 2:29:03 AM
 *  Author: ahmed
 */ 
#include "BIT_MATH.h"
#include "DIO_INT.h"
#include "STD_TYPES.h"
#include "DIO_REG.h"
//#include <avr/io.h>

void DIO_VoidSetPinDirection(u8 pin_number,u8 port_number,u8 direction)
{
	switch(port_number)
	{
		case portA:
			if (direction==OUTPUT)
			{
				SET_Bit(DDRA_REG,pin_number);
			}
			else if (direction==INPUT)
			{
				CLEAR_Bit(DDRA_REG,pin_number);
			}
			break;
		case portB:
			if (direction==OUTPUT)
			{
				SET_Bit(DDRB_REG,pin_number);
			}
			else if (direction==INPUT)
			{
				CLEAR_Bit(DDRB_REG,pin_number);
			}
			break;
		case portC:
			if (direction==OUTPUT)
			{
				SET_Bit(DDRC_REG,pin_number);
			}
			else if (direction==INPUT)
			{
				CLEAR_Bit(DDRC_REG,pin_number);
			}
			break;
		case portD:
			if (direction==OUTPUT)
			{
				SET_Bit(DDRD_REG,pin_number);
			}
			else if (direction==INPUT)
			{
				CLEAR_Bit(DDRD_REG,pin_number);
			}
			break;

	}
}


void DIO_VoidSetPinValue(u8 pin_number,u8 port_number,u8 value)
{
	switch(port_number)
	{
		case portA:
			if (value==HIGH)
			{
				SET_Bit(PORTA_REG,pin_number);
			}
			else if (value==LOW)
			{
				CLEAR_Bit(PORTA_REG,pin_number);
			}
			break;
		case portB:
			if (value==HIGH)
			{
				SET_Bit(PORTB_REG,pin_number);
			}
			else if (value==LOW)
			{
				CLEAR_Bit(PORTB_REG,pin_number);
			}
			break;
		
		case portC:
			if (value==HIGH)
			{
				SET_Bit(PORTC_REG,pin_number);
			}
			else if (value==LOW)
			{
				CLEAR_Bit(PORTC_REG,pin_number);
			}
			break;
		case portD:
			if (value==HIGH)
			{
				SET_Bit(PORTD_REG,pin_number);
			}
			else if (value==LOW)
			{
				CLEAR_Bit(PORTD_REG,pin_number);
			}
			break;
	}
}


void DIO_VoidSetPortDirection(u8 port_number,u8 direction)
{
	u8 pinnumber=8;
	switch(port_number)
	{
		case portA:
			if (direction==OUTPUT)
			{
				for (u16 i=0; i<pinnumber; i++)
				{
					SET_Bit(DDRA_REG,i);
				}
			}
			else if (direction==INPUT)
			{
				for (u16 i=0; i<pinnumber; i++)
				{
					CLEAR_Bit(DDRA_REG,i);
				}
			}
		break;
		case portB:
			if (direction==OUTPUT)
			{
				for (u16 i=0; i<pinnumber; i++)
				{
					SET_Bit(DDRB_REG,i);
				}
			}
			else if (direction==INPUT)
			{
				for (u16 i=0; i<pinnumber; i++)
				{
					CLEAR_Bit(DDRB_REG,i);
				}
			}
			break;
		case portC:
			if (direction==OUTPUT)
			{
				for (u16 i=0; i<pinnumber; i++)
				{
					SET_Bit(DDRC_REG,i);
				}
			}
			else if (direction==INPUT)
			{
				for (u16 i=0; i<pinnumber; i++)
				{
					CLEAR_Bit(DDRC_REG,i);
				}
			}
			break;
		case portD:
			if (direction==OUTPUT)
			{
				for (u16 i=0; i<pinnumber; i++)
				{
					SET_Bit(DDRD_REG,i);
				}
			}
			else if (direction==INPUT)
			{
				for (u16 i=0; i<pinnumber; i++)
				{
					CLEAR_Bit(DDRD_REG,i);
				}
			}
			break;
	}
}


void DIO_VoidSetPortValue(u8 port_number,u8 value)
{
	switch(port_number)
	{
		case portA:
			PORTA_REG =value;
			break;
		case portB:
			PORTB_REG =value;
			break;
		case portC:
			PORTC_REG =value;
			break;
		case portD:
			PORTD_REG =value;
			break;
	}
}


u8 DIO_U8GetPinValue(u8 pin_number,u8 port_number)
{
	u8 pinvalue=2;

	switch(port_number)
	{
		case portA:
			pinvalue = GET_Bit(PINA_REG,pin_number);
			//return ((GET_Bit(port_number,pin_number)) & (0X01));
			break;
		case portB:
			pinvalue = GET_Bit(PINB_REG,pin_number);
			//return ((GET_Bit(port_number,pin_number)) & (0X01));
			break;
		case portC:
			pinvalue = GET_Bit(PINC_REG,pin_number);
			//return ((GET_Bit(port_number,pin_number)) & (0X01));
			break;
		case portD:
			pinvalue = GET_Bit(PIND_REG,pin_number);
			//return ((GET_Bit(port_number,pin_number)) & (0X01));
			break;

	}
	
	return ((pinvalue) & (0X01));
}