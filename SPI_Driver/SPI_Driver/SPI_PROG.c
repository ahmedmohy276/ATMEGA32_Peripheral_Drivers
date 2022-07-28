/*
 * SPI_PROG.c
 *
 * Created: 10/9/2021 12:17:07 AM
 *  Author: ahmed
 */ 

#define F_CPU 2000000

#include "STD_TYPES.h"
#include "DIO_INT.h"
#include "DIO_REG.h"
#include "BIT_MATH.h"
#include "SPI_CONFIG.h"
#include "SPI_REGISTERS.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

void (*SPI_ptr) (void);

u8 status=NORMAL;
u8* TX_DATA;
//u8* received_Data;
//u8 received_Data[DATA_SIZE];
u16 counter=1;
u16 data_size=DATA_SIZE;



void SPI_VoidMasterInit(void)
{
	DIO_VoidSetPinDirection(SS_PIN,SPI_PORT,OUTPUT);
	DIO_VoidSetPinValue(SS_PIN,SPI_PORT,LOW);
	DIO_VoidSetPinDirection(MOSI_PIN,SPI_PORT,OUTPUT);
	DIO_VoidSetPinDirection(MISO_PIN,SPI_PORT,INPUT);
	DIO_VoidSetPinDirection(SCK_PIN,SPI_PORT,OUTPUT);
	SET_Bit(SPCR_REG,4);
	SET_Bit(SPCR_REG,6);
}

void SPI_VoidSlaveInit(void)
{
	DIO_VoidSetPinDirection(SS_PIN,SPI_PORT,INPUT);
	DIO_VoidSetPinDirection(MOSI_PIN,SPI_PORT,INPUT);
	DIO_VoidSetPinDirection(MISO_PIN,SPI_PORT,OUTPUT);
	DIO_VoidSetPinDirection(SCK_PIN,SPI_PORT,INPUT);
	CLEAR_Bit(SPCR_REG,4);
	SET_Bit(SPCR_REG,6);
}


void SPI_VoidInterruptEnable(u8 status)
{
	switch (status)
	{ 
		case INT_ENABLE :
			SET_Bit(SPCR_REG,7);
			SET_Bit(SREG_REG,7);
			break;
		
		case INT_DISABLE :
			CLEAR_Bit(SPCR_REG,7);
			break;
	}
}

void SPI_VoidSetDataOrder(u8 data_order)
{
	switch (data_order)
	{
		case LSB_ORDER :
			SET_Bit(SPCR_REG,5);
			break;
		
		case MSB_ORDER :
			CLEAR_Bit(SPCR_REG,5);
			break;
	}
}


void SPI_VoidSetClockPolarity(u8 clk_polarity)
{
	switch (clk_polarity)
	{
		case RISING_FALLING :
			CLEAR_Bit(SPCR_REG,3);
			break;
		
		case FALLING_RISING :
			SET_Bit(SPCR_REG,3);
			break;
	}
}

void SPI_VoidSetClockPhase(u8 clk_phase)
{
	switch (clk_phase)
	{
		case SAMPLE_SETUP :
			CLEAR_Bit(SPCR_REG,2);
			break;
			
		case SETUP_SAMPLE :
			SET_Bit(SPCR_REG,2);
			break;
	}
}

void SPI_VoidSetClockRate(u8 clk_Rate)
{
	switch (clk_Rate)
	{
		case FOSC_4 :
			CLEAR_Bit(SPCR_REG,0);
			CLEAR_Bit(SPCR_REG,1);
			break;
		
		case FOSC_16 :
			SET_Bit(SPCR_REG,0);
			CLEAR_Bit(SPCR_REG,1);
			break;
			
		case FOSC_64 :
			CLEAR_Bit(SPCR_REG,0);
			SET_Bit(SPCR_REG,1);
			break;
		
		case FOSC_128 :
			SET_Bit(SPCR_REG,0);
			SET_Bit(SPCR_REG,1);
			break;
	}
}

void SPI_VoidSetDoubleSpeed(u8 status)
{
	switch(status)
	{
		case DOUBLE_SPEED_ON :
			SET_Bit(SPSR_REG,0);
			break;
		
		case DOUBLE_SPEED_OFF :
			CLEAR_Bit(SPSR_REG,0);
			break;
	}
}

void SPI_VoidSPIInitialization(u8 Mode,u8 INT_status,u8 data_order,u8 clk_polarity,u8 clk_phase,u8 clk_Rate,u8 double_speed_status)
{
	SPI_VoidInterruptEnable(INT_status);

	SPI_VoidSetDataOrder(data_order);

	SPI_VoidSetClockPolarity(clk_polarity);

	SPI_VoidSetClockPhase(clk_phase);

	SPI_VoidSetClockRate(clk_Rate);

	SPI_VoidSetDoubleSpeed(double_speed_status);
	
	switch (Mode)
	{
		case MASTER :
		SPI_VoidMasterInit();
		break;
		
		case SLAVE :
		SPI_VoidSlaveInit();
		break;
	}
}

/*void SPI_VoidSeCallBackFunc(void (*receive_asynch) (u8))
{
	SPI_ptr=receive_asynch;
	status=NORMAL;
}*/

void SPI_VoidSeCallBackFunc(void (*ptrToFunc) (void))
{
	SPI_ptr=ptrToFunc;
	status=NORMAL;
}

u8 SPI_U8_SynchSendData(u8 data)
{
	SPDR_REG=data;
	while(GET_Bit(SPSR_REG,7) !=1);
	return SPDR_REG;
}

u8* SPI_U8_SynchSendString(u8* data)
{
	u16 i=0;
	while(data[i] !='\0')
	{
		data[i]=SPI_U8_SynchSendData(data[i]);
		i++;
	}
	//data[i]=SPI_U8_SynchSendData(END_FLAG);
	return data;
}

void SPI_VoidASynchSendData(u8 data)
{
	SPI_VoidInterruptEnable(INT_ENABLE);
	SPDR_REG=data;
	status=ASYNCH_char;
}

void SPI_VoidASynchSendString(u8 *data)
{
	SPI_VoidInterruptEnable(INT_ENABLE);
	TX_DATA=data;
	if (TX_DATA[0] !='\0')
	{
		status=TRANSMITT_ASYNCH_arr;
		SPDR_REG=TX_DATA[0];
	}
}

u8 SPI_U8_SynchReceiveData(u8 data)
{
	SPDR_REG=data;
	while(GET_Bit(SPSR_REG,7) !=1);
	return SPDR_REG;
}

u8* SPI_U8_SynchReceiveString(u8 *data)
{
	u16 i=0;
	while(i !=DATA_SIZE)
	{
		data[i]=SPI_U8_SynchReceiveData(data[i]);
		i++;
	}
	return data;
}

void SPI_VoidASynchReceiveData(u8 data,u8* data_received)
{
	SPI_VoidInterruptEnable(INT_ENABLE);
	data_received = &SPI_DATA;
	SPDR_REG=data;
	status=ASYNCH_char;
}


void SPI_VoidASynchReceiveString(u8 *data,u8* data_received)
{
	SPI_VoidInterruptEnable(INT_ENABLE);
	data_received=&received_Data;
	TX_DATA=data;
	status=RECEIVE_ASYNCH_arr;
	SPDR_REG=TX_DATA[0];
}

ISR(SPI_STC_vect)
{
	switch (status)
	{
		case ASYNCH_char:
			SPI_DATA=SPDR_REG;
			break;
			
		case TRANSMITT_ASYNCH_arr:
			if (TX_DATA[counter] !='\0')
			{
				received_Data[counter-1]=SPDR_REG;
				SPDR_REG=TX_DATA[counter];
				counter++;
			} 
			
			else if (TX_DATA[counter] =='\0')
			{
				//received_Data[counter]=SPDR_REG;
				//SPDR_REG =END_FLAG;
				counter=1;
				status=NORMAL;
			}
			break;
			
		case RECEIVE_ASYNCH_arr:
			//received_Data[counter-1]=SPDR_REG;
			//if (received_Data[counter-1] !=END_FLAG)
			if (counter <=data_size)
			{
				received_Data[counter-1]=SPDR_REG;
				SPDR_REG=TX_DATA[counter];
				counter++;
			}
			//else if (received_Data[counter-1] ==END_FLAG)
			else if (counter >data_size)
			{
				counter=1;
				status=NORMAL;
			}
			break;
		
		case NORMAL:
			SPI_ptr();
			break;
	}

}

/*ISR(SPI_STC_vect)
{
	if (SPI_ptr!=0)
	{
		SPI_ptr(SPDR_REG);
	}
}*/