/*
 * UART_INTERFACE.h
 *
 * Created: 10/4/2021 6:41:09 PM
 *  Author: ahmed
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "STD_TYPES.h"


void UART_VoidInit(void);

void UART_VoidParityBit(u8 status);

void UART_VoidSetMode(u8 Mode);

void UART_VoidSeCharSize(u8 char_size);

void UART_VoidSetBaudeRate(u16 baudrate,u8 Mode,u64 Fosc);

void UART_VoidStopBit(u8 stop_bits_number);

void UART_VoidSetSYNCHModeCLKPolarity(u8 clock_polarity);

/************************************************************************/
/*                              TX                                      */
/************************************************************************/

void UART_VoidTXINTEnable(u8 status);

void UART_VoidSYNCHSendChar(u8 character);

void UART_VoidSYNCHSendString(u8* string_ptr);

void UART_VoidASYNCHSendChar(u8 character);

void UART_VoidTXSetCallBack(void (*ptrToFunc) (void));

void UART_VoidASYNCHSendString(u8* string_ptr);

/************************************************************************/
/*                               RX                                     */
/************************************************************************/

u8 UART_VoidSYNCHReceiveChar(u8 character);

void UART_VoidASYNCHReceiveChar(void);

void UART_VoidASYNCHReceiveData(u8* data);

void UART_VoidRXSetCallBack(void (*ptrToFunc) (void));

void UART_VoidRXINTEnable(u8 status);

#endif /* UART_INTERFACE_H_ */