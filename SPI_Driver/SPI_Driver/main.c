/*
 * SPI_Driver.c
 *
 * Created: 10/9/2021 12:14:12 AM
 * Author : ahmed
 */ 

//#include <avr/io.h>

#define F_CPU 2000000

#include "STD_TYPES.h"
#include "DIO_INT.h"
#include "BIT_MATH.h"
#include "SPI_CONFIG.h"
#include "SPI_INTERFACE.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


int main(void)
{

    /* Replace with your application code */
	u8 T_data=1;
	u8 R_data;
	u8 arr[] ={1,2,4,8,15,'\0'};
	u8 *str_arr="Hello";
	u8* ptr;
	/*u8* ptr =(u8*)malloc(5*sizeof(u8));
	ptr[0] =1;
	ptr[1] =2;
	ptr[2] =4;
	ptr[3] =8;
	ptr[4] =15;
	ptr[5] ='\0';*/
	
	DIO_VoidSetPortDirection(portC,OUTPUT);
	DIO_VoidSetPortDirection(portA,INPUT);
	DIO_VoidSetPortValue(portA,0XFF);
	

	/*SPI_VoidSetClockRate(FOSC_16);
	SPI_VoidInterruptEnable(INT_DISABLE);
	SPI_VoidSetDoubleSpeed(DOUBLE_SPEED_OFF);
	SPI_VoidSetDataOrder(MSB_ORDER);
	SPI_VoidSetClockPolarity(RISING_FALLING);
	SPI_VoidSetClockPhase(SAMPLE_SETUP);
	SPI_VoidMasterInit();*/
	SPI_VoidSPIInitialization(MASTER,INT_DISABLE,MSB_ORDER,RISING_FALLING,SAMPLE_SETUP,FOSC_128,DOUBLE_SPEED_OFF);
	
	_delay_ms(100);
	
	
	/************************************************************************/
	/*                       Synchronous functions test                     */
	/************************************************************************/
	
	//R_data=SPI_U8_SynchSendData(T_data);
	
	/*R_data=SPI_U8_SynchSendData(arr[1]);
	R_data=SPI_U8_SynchSendData(arr[2]);
	R_data=SPI_U8_SynchSendData(arr[3]);
	R_data=SPI_U8_SynchSendData(arr[4]);*/
	
	ptr =SPI_U8_SynchSendString(arr);
	
	/************************************************************************/
	/*                       ASynchronous functions test                    */
	/************************************************************************/
	
	
	//SPI_VoidASynchSendData(T_data);
	/*_delay_ms(50);
	SPI_VoidASynchSendData(arr[1]);
	_delay_ms(50);
	SPI_VoidASynchSendData(arr[2]);
	_delay_ms(50);
	SPI_VoidASynchSendData(arr[3]);
	_delay_ms(50);
	SPI_VoidASynchSendData(arr[4]);*/

	//SPI_VoidASynchSendString(arr);
	
	//DIO_VoidSetPortValue(portC,R_data);
	while (1) 
    {
		/*T_data=PINA;
		R_data=SPI_U8_SynchSendData(T_data);
		DIO_VoidSetPortValue(portC,R_data);
		_delay_ms(1000);*/
    }
	
	free(ptr);
}

