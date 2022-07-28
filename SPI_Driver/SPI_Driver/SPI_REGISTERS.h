
/*
 * SPI_REGISTERS.h
 *
 * Created: 10/9/2021 12:53:24 AM
 *  Author: ahmed
 */ 


#ifndef SPI_REGISTERS_H_
#define SPI_REGISTERS_H_
#include "STD_TYPES.h"

#define SREG_REG				     	(*((volatile u8*) 0X5F))

#define SPCR_REG                        (*((volatile u8*) 0X2D))

#define SPSR_REG                        (*((volatile u8*) 0X2E))

#define SPDR_REG                        (*((volatile u8*) 0X2F))


#endif /* SPI_REGISTERS_H_ */