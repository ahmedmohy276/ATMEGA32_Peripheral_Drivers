/*
 * I2C_PROG.c
 *
 * Created: 10/31/2021 1:53:33 PM
 *  Author: ahmed
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "I2C_CONFIG.h"
#include "I2C_REGISTERS.h"


static void TWI_VoidSetPrescaler(u8 Prescaler)
{
	switch (Prescaler)
	{
		case PRESCALER_1:
			CLEAR_Bit(TWSR_REG,0);
			CLEAR_Bit(TWSR_REG,1);
			break;
		
		case PRESCALER_4:
			SET_Bit(TWSR_REG,0);
			CLEAR_Bit(TWSR_REG,1);
			break;
		
		case PRESCALER_16:
			CLEAR_Bit(TWSR_REG,0);
			SET_Bit(TWSR_REG,1);
			break;
		
		case PRESCALER_64:	
			SET_Bit(TWSR_REG,0);
			SET_Bit(TWSR_REG,1);
			break;
	
	}
}


static void TWI_VoidInterruptStatus(u8 INT_status)
{
	switch (INT_status)
	{
		case ENABLE_INT:
			SET_Bit(TWCR_REG,0);
			SET_Bit(SREG_REG,7);
			break;
		
		case DISABLE_INT:
			CLEAR_Bit(TWSR_REG,0);
			break;
	}
}


static void TWI_VoidSendStartCond(void)
{
	//save values of TWEN & TWIE bits
	TWCR_REG &=0X07;
	//clear TWINT flag
	SET_Bit(TWCR_REG,7);
	//send start condition
	SET_Bit(TWCR_REG,5);
	//wait start condition to be transmitted
	while(GET_Bit(TWCR_REG,7) ==0);
}


static void TWI_VoidSendStopCond(void)
{
	//save values of TWEN & TWIE bits
	TWCR_REG &=0X07;
	//clear TWINT flag
	SET_Bit(TWCR_REG,7);
	//send stop condition
	SET_Bit(TWCR_REG,4);
	//wait stop condition to be transmitted
	while(GET_Bit(TWCR_REG,7) ==0);
}


static void TWI_VoidWriteData(u8 Data)
{
	//save values of TWEN & TWIE bits
	TWCR_REG &=0X07;
	TWDR_REG=Data;
	//clear TWINT flag
	SET_Bit(TWCR_REG,7);
	//wait data to be transmitted
	while(GET_Bit(TWCR_REG,7) ==0);
}


static u8 TWI_u8_ReadData_ACK(void)
{
	//save values of TWEN & TWIE bits
	TWCR_REG &=0X07;
	//clear TWINT flag
	SET_Bit(TWCR_REG,7);
	//send ACK for received data
	SET_Bit(TWCR_REG,6);
	//wait data to be received
	while(GET_Bit(TWCR_REG,7) ==0);
	return TWDR_REG;
}


static u8 TWI_u8_ReadData_NACK(void)
{
	//save values of TWEN & TWIE bits
	TWCR_REG &=0X07;
	//clear TWINT flag
	SET_Bit(TWCR_REG,7);
	//send NACK for received data
	CLEAR_Bit(TWCR_REG,6);
	//wait data to be received
	while(GET_Bit(TWCR_REG,7) ==0);
	return TWDR_REG;
}


static u8 TWI_u8_GetStatus(void)
{
	return ((TWSR_REG) & (0XF8));
}


void TWI_VoidInit(u8 Prescaler,u8 Address,u8 INT_status)
{
	TWI_VoidInterruptStatus(INT_status);
	//set Address value
	TWAR_REG =Address;
	//set bit rate value
	TWBR_REG =((u32)FOSC-16*(u32)SCL_FREQUENCY)/(2*(u32)SCL_FREQUENCY*Prescaler);
	//set Prescaler
	TWI_VoidSetPrescaler(Prescaler);
	//enable I2C
	SET_Bit(TWCR_REG,2);
}

void TWI_VoidWriteByte(u8 SlaveAddress,u8 InternalRegAddress,u8 Data)
{
	//start condition
	TWI_VoidSendStartCond();
	if (TWI_u8_GetStatus() !=START_COND_CODE)
	{
		//error
	}
	//Slave address + write
	TWI_VoidWriteData((SlaveAddress<<1) | (WRITEMODE));
	//wait ACK
	if (TWI_u8_GetStatus() !=SLA_WR_ACK_CODE)
	{
		//error
	}
	//register address
	TWI_VoidWriteData(InternalRegAddress);
	//wait ACK
	if (TWI_u8_GetStatus() !=DATA_WR_ACK_CODE)
	{
		//error
	}
	//Byte to be written
	TWI_VoidWriteData(Data);
	//wait ACK
	if (TWI_u8_GetStatus() !=DATA_WR_ACK_CODE)
	{
		//error
	}
	//stop condition
	TWI_VoidSendStopCond();
}

u8 TWI_VoidReadByte(u8 SlaveAddress,u8 InternalRegAddress)
{
	u8 RXData=0;
	//start condition
	TWI_VoidSendStartCond();
	
	if (TWI_u8_GetStatus() !=START_COND_CODE)
	{
		//error
	}
	//Slave address + write
	TWI_VoidWriteData((SlaveAddress<<1) | (WRITEMODE));
	//wait ACK
	if (TWI_u8_GetStatus() !=SLA_WR_ACK_CODE)
	{
		//error
	}
	//register address
	TWI_VoidWriteData(InternalRegAddress);
	//wait ACK
	if (TWI_u8_GetStatus() !=DATA_WR_ACK_CODE)
	{
		//error
	}
	//repeated start condition
	TWI_VoidSendStartCond();
	
	if (TWI_u8_GetStatus() !=REPEATED_START_COND_CODE)
	{
		//error
	}
	//Slave address + read
	TWI_VoidWriteData((SlaveAddress<<1) | (READMODE));
	//wait ACK
	if (TWI_u8_GetStatus() !=SLA_RE_ACK_CODE)
	{
		//error
	}
	//read received data with NACK
	RXData=TWI_u8_ReadData_NACK();
	if (TWI_u8_GetStatus() !=DATA_RE_NACK_CODE)
	{
		//error
	}
	
	//stop condition
	TWI_VoidSendStopCond();
	return RXData;
}