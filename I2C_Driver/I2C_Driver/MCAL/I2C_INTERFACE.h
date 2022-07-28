/*
 * I2C_INTERFACE.h
 *
 * Created: 10/31/2021 1:52:23 PM
 *  Author: ahmed
 */ 


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#include "STD_TYPES.h"


void TWI_VoidInit(u8 Prescaler,u8 Address,u8 INT_status);

void TWI_VoidWriteByte(u8 SlaveAddress,u8 InternalRegAddress,u8 Data);

u8 TWI_VoidReadByte(u8 SlaveAddress,u8 InternalRegAddress);

#endif /* I2C_INTERFACE_H_ */