/*
 * UART_REGISTERS.h
 *
 * Created: 10/4/2021 6:50:44 PM
 *  Author: ahmed
 */ 


#ifndef UART_REGISTERS_H_
#define UART_REGISTERS_H_


#define SREG_REG				(*((volatile u8*) 0X5F))

#define UDR_REG					(*((volatile u8*) 0X2C))

#define UCSRA_REG				(*((volatile u8*) 0X2B))

#define UCSRB_REG				(*((volatile u8*) 0X2A))

#define UCSRC_REG				(*((volatile u8*) 0X40))

#define UBRRL_REG				(*((volatile u8*) 0X29))

#define UBRRH_REG				(*((volatile u8*) 0X40))


#endif /* UART_REGISTERS_H_ */