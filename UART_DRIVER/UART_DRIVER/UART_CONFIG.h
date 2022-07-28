/*
 * UART_CONFIG.h
 *
 * Created: 10/4/2021 6:41:49 PM
 *  Author: ahmed
 */ 

#include "STD_TYPES.h"

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

u8 RX_received_char;
u8 RX_array[100];

#define TX_ENABLE						0
#define RX_ENABLE						1
#define TX_INT_ENABLE				    2
#define TX_INT_DISABLE			     	3
#define SYNCH_MODE						4
#define ASYNCH_NORMAL_MODE				5
#define ASYNCH_DOUBLE_SPEED_MODE		23
#define EVEN_PARITY						6
#define ODD_PARITY						7	
#define DISABLE_PARITY					8
#define RESERVED						9
#define STOP_BIT_1					    10
#define STOP_BIT_2				     	11
#define CHAR_SIZE_5						12
#define CHAR_SIZE_6						13
#define CHAR_SIZE_7						14
#define CHAR_SIZE_8						15
#define CHAR_SIZE_9						16
#define RISING_FALLING					17
#define FALLING_RISING					18
#define TX_DISABLE						19
#define RX_DISABLE						20
#define RX_INT_ENABLE				    21
#define RX_INT_DISABLE			     	22


#define NORMAL                          0
#define ASYNCH_char_TX					1
#define ASYNCH_arr_TX					2
#define ASYNCH_char_RX					3
#define ASYNCH_arr_RX					4




#define FOSC							2000000
#define BAUD_RATE                       2400


#define RX_PIN                         0
#define TX_PIN                         1


#define END_FLAG                       '\0'

#endif /* UART_CONFIG_H_ */