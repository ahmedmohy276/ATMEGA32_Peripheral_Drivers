/*
 * DIO_INT.h
 *
 * Created: 9/14/2021 2:28:16 AM
 *  Author: ahmed
 */ 

#include "STD_TYPES.h"

#ifndef DIO_INT_H_
#define DIO_INT_H_


typedef enum
{
	INPUT,
	OUTPUT,
	portA,
	portB,
	portC,
	portD,
	HIGH  =1,
	LOW  =0,
	
}DIO_Status;


void DIO_VoidSetPinDirection(u8 pin_number,u8 port_number,u8 direction);
void DIO_VoidSetPinValue(u8 pin_number,u8 port_number,u8 value);

void DIO_VoidSetPortDirection(u8 port_number,u8 direction);
void DIO_VoidSetPortValue(u8 port_number,u8 value);

u8 DIO_U8GetPinValue(u8 pin_number,u8 port_number);
u8 DIO_U8GetPortValue(u8 port_number);

void DIO_VoidSetHigh4BitDirection(u8 port_number,u8 Direction);
void DIO_VoidSetHigh4BitValue(u8 port_number,u8 value);


void DIO_VoidSetLow4BitDirection(u8 port_number,u8 Direction);
void DIO_VoidSetLow4BitValue(u8 port_number,u8 value);


#endif /* DIO_INT_H_ */