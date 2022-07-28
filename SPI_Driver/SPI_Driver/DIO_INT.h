/*
 * DIO_INT.h
 *
 * Created: 9/14/2021 2:28:16 AM
 *  Author: ahmed
 */ 

#include "STD_TYPES.h"

#ifndef DIO_INT_H_
#define DIO_INT_H_

#define portA  0
#define portB  1
#define portC  2
#define portD  3

#define OUTPUT 1
#define INPUT  0

#define  HIGH  1
#define  LOW   0


void DIO_VoidSetPinDirection(u8 pin_number,u8 port_number,u8 direction);
void DIO_VoidSetPinValue(u8 pin_number,u8 port_number,u8 value);

void DIO_VoidSetPortDirection(u8 port_number,u8 direction);
void DIO_VoidSetPortValue(u8 port_number,u8 value);

u8 DIO_U8GetPinValue(u8 pin_number,u8 port_number);


#endif /* DIO_INT_H_ */