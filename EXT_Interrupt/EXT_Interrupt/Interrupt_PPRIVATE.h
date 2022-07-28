/*
 * Interrupt_REG.h
 *
 * Created: 9/25/2021 1:03:16 PM
 *  Author: ahmed
 */ 


#ifndef INTERRUPT_REG_H_
#define INTERRUPT_REG_H_

#define SREG_REG					(*((volatile u8*) 0X5F))

#define GICR_REG					(*((volatile u8*) 0X5B))

#define GIFR_REG					(*((volatile u8*) 0X5A))

#define MCUCR_REG					(*((volatile u8*) 0X55))

#define MCUCSR_REG					(*((volatile u8*) 0X54))

#endif /* INTERRUPT_REG_H_ */