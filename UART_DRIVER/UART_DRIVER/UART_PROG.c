/*
 * UART_PROG.c
 *
 * Created: 10/4/2021 6:41:29 PM
 *  Author: ahmed
 */ 
#define F_CPU 2000000


#include "UART_REGISTERS.h"
#include "UART_CONFIG.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>

u8 status=NORMAL;

u8* TX_string_ptr;

u8* RX_data;

u16 TX_count=1;

u8 RX_count=0;

void (*TXptr) (void);

void (*RXptr) (void);



void UART_VoidInit(void)
{
	/**Enable TX and RX**/
	SET_Bit(UCSRB_REG,3);
	SET_Bit(UCSRB_REG,4);
}

void UART_VoidParityBit(u8 status)
{
	switch(status)
	{
		case DISABLE_PARITY :
			SET_Bit(UCSRC_REG,7);
			CLEAR_Bit(UCSRC_REG,4);
			CLEAR_Bit(UCSRC_REG,5);
			break;
		
		case RESERVED :	
			SET_Bit(UCSRC_REG,7);
			SET_Bit(UCSRC_REG,4);
			CLEAR_Bit(UCSRC_REG,5);
			break;
		
		case EVEN_PARITY :
			//UCSRC_REG =(1<<7) | (1<<5);
			SET_Bit(UCSRC_REG,7);
			CLEAR_Bit(UCSRC_REG,4);
			SET_Bit(UCSRC_REG,5);
			break;
		
		case ODD_PARITY :
			SET_Bit(UCSRC_REG,7);
			SET_Bit(UCSRC_REG,4);
			SET_Bit(UCSRC_REG,5);
			break;
		
	}
}

void UART_VoidSetMode(u8 Mode)
{
	switch(Mode)
	{
		case ASYNCH_NORMAL_MODE :
			SET_Bit(UCSRC_REG,7);
			CLEAR_Bit(UCSRC_REG,6);
			CLEAR_Bit(UCSRA_REG,1);
			break;
		
		case ASYNCH_DOUBLE_SPEED_MODE :
			SET_Bit(UCSRC_REG,7);
			CLEAR_Bit(UCSRC_REG,6);
			SET_Bit(UCSRA_REG,1);
			break;
		
		case SYNCH_MODE :
			SET_Bit(UCSRC_REG,7);
			SET_Bit(UCSRC_REG,6);
			CLEAR_Bit(UCSRA_REG,6);
			break;
	}
}

void UART_VoidSeCharSize(u8 char_size)
{
	switch(char_size)
	{
		case CHAR_SIZE_5 :
			SET_Bit(UCSRC_REG,7);
			CLEAR_Bit(UCSRC_REG,1);
			CLEAR_Bit(UCSRC_REG,2);
			CLEAR_Bit(UCSRB_REG,2);
			break;
		
		case CHAR_SIZE_6 :
			SET_Bit(UCSRC_REG,7);
			SET_Bit(UCSRC_REG,1);
			CLEAR_Bit(UCSRC_REG,2);
			CLEAR_Bit(UCSRB_REG,2);
			break;
		
		case CHAR_SIZE_7 :
			SET_Bit(UCSRC_REG,7);
			CLEAR_Bit(UCSRC_REG,1);
			SET_Bit(UCSRC_REG,2);
			CLEAR_Bit(UCSRB_REG,2);
			break;
		
		case CHAR_SIZE_8 :
			SET_Bit(UCSRC_REG,7);
			SET_Bit(UCSRC_REG,1);
			SET_Bit(UCSRC_REG,2);
			CLEAR_Bit(UCSRB_REG,2);
			break;
		
		case RESERVED :
			SET_Bit(UCSRC_REG,7);
			CLEAR_Bit(UCSRC_REG,1);
			CLEAR_Bit(UCSRC_REG,2);
			SET_Bit(UCSRB_REG,2);
			break;
		
		case CHAR_SIZE_9 :
			SET_Bit(UCSRC_REG,7);
			SET_Bit(UCSRC_REG,1);
			SET_Bit(UCSRC_REG,2);
			SET_Bit(UCSRB_REG,2);
			break;
	}
}

void UART_VoidSetBaudeRate(u16 baudrate,u8 Mode,u64 Fosc)
{
	u16 volatile value=0;
	switch(Mode)
	{
		case ASYNCH_NORMAL_MODE :
			value = (u16)(((u32)FOSC/(16*(u32)BAUD_RATE))-1);
			UBRRH_REG = (u8)(value>>8) ;
			UBRRL_REG = (u8)(value);
			break;
		
		case ASYNCH_DOUBLE_SPEED_MODE :
			value = (u16)(((u32)FOSC/(8*(u32)BAUD_RATE))-1);
			UBRRH_REG = (u8)(value>>8) ;
			UBRRL_REG = (u8)(value);
			break;
		
		case SYNCH_MODE :
			value = (u16)(((u32)FOSC/(2*(u32)BAUD_RATE))-1);
			UBRRH_REG = (u8)(value>>8) ;
			UBRRL_REG = (u8)(value);
			break;
	}
	
}

void UART_VoidStopBit(u8 stop_bits_number)
{
	switch(stop_bits_number)
	{
		case STOP_BIT_1 :
			SET_Bit(UCSRC_REG,7);
			CLEAR_Bit(UCSRC_REG,3);
			break;
			
		case STOP_BIT_2 :
			SET_Bit(UCSRC_REG,7);
			SET_Bit(UCSRC_REG,3);
			break;
	}
}

void UART_VoidSetSYNCHModeCLKPolarity(u8 clock_polarity)
{
	switch(clock_polarity)
	{
		case RISING_FALLING :
			SET_Bit(UCSRC_REG,7);
			CLEAR_Bit(UCSRC_REG,0);
			break;
		
		case FALLING_RISING :
			SET_Bit(UCSRC_REG,7);
			SET_Bit(UCSRC_REG,0);
			break;
	}
}


/************************************************************************/
/*                              TX                                      */
/************************************************************************/

void UART_VoidTXINTEnable(u8 status)
{
	switch(status)
	{
		case TX_INT_ENABLE :
			SET_Bit(UCSRB_REG,6);
			SET_Bit(SREG_REG,7);
			break;
		
		case TX_INT_DISABLE :
			CLEAR_Bit(UCSRB_REG,6);
			break;
	}
}

void UART_VoidSYNCHSendChar(u8 character)
{
	while(GET_Bit(UCSRA_REG,5) !=1);
	UDR_REG=character;
	while(GET_Bit(UCSRA_REG,6) !=1);
}

void UART_VoidSYNCHSendString(u8* string_ptr)
{
	u16 i=0;
	while(string_ptr[i] !='\0')
	{
		UART_VoidSYNCHSendChar(string_ptr[i]);
		i++;
	}
	UART_VoidSYNCHSendChar(END_FLAG);
}

void UART_VoidASYNCHSendChar(u8 character)
{
	UART_VoidRXINTEnable(TX_INT_ENABLE);
	while(GET_Bit(UCSRA_REG,5) !=1);
	UDR_REG=character;
	status=ASYNCH_char_TX;
}

void UART_VoidASYNCHSendString(u8* string_ptr)
{
	UART_VoidTXINTEnable(TX_INT_ENABLE);
	TX_string_ptr=string_ptr;
	if (TX_string_ptr[0] !='\0')
	{
		while(GET_Bit(UCSRA_REG,5) !=1);
		status=ASYNCH_arr_TX;
		UDR_REG=TX_string_ptr[0];
	}
}



void UART_VoidTXSetCallBack(void (*ptrToFunc) (void))
{
	status=NORMAL;
	TXptr=ptrToFunc;
}


/************************************************************************/
/*                               RX                                     */
/************************************************************************/
void UART_VoidRXINTEnable(u8 status)
{
	switch(status)
	{
		case RX_INT_ENABLE :
			SET_Bit(UCSRB_REG,7);
			SET_Bit(SREG_REG,7);
			break;
		
		case RX_INT_DISABLE :
			CLEAR_Bit(UCSRB_REG,7);
			break;
	}
}


void UART_VoidASYNCHReceiveChar(void)
{
	UART_VoidRXINTEnable(RX_INT_ENABLE);
	status=ASYNCH_char_RX;
}

void UART_VoidASYNCHReceiveData(u8* data)
{
	UART_VoidRXINTEnable(RX_INT_ENABLE);
	status=ASYNCH_arr_RX;
	data=RX_data;
}


void UART_VoidRXSetCallBack(void (*ptrToFunc) (void))
{
	status=NORMAL;
	RXptr=ptrToFunc;
}




ISR(USART_TXC_vect)
{
	switch (status)
	{
		
		case ASYNCH_char_TX :
		
			break;
		
		case ASYNCH_arr_TX :
			if (TX_string_ptr[TX_count] !='\0')
			{
				UDR_REG=TX_string_ptr[TX_count];
				TX_count++;
			}
			
			else if (TX_string_ptr =='\0')
			{
				UDR_REG=END_FLAG;
				TX_count=1;
				status=NORMAL;
			}
			break;
		
		case NORMAL :
			TXptr();
			break;
	}
}



ISR(USART_RXC_vect)
{
	switch (status)
	{
		case ASYNCH_char_RX :
			RX_received_char=UDR_REG;
			break;
		
		case ASYNCH_arr_RX :
			RX_array[RX_count] =UDR_REG;
			if (RX_array[RX_count] !=END_FLAG)
			{
				RX_count++;
			}
			
			else if (RX_array[RX_count] ==END_FLAG)
			{
				RX_array[RX_count] =END_FLAG;
				RX_count=0;
				status=NORMAL;
			}
			
			break;
		
		case NORMAL :
			RXptr();
			break;
	}
}