/*
 * LCD_PROG.c
 *
 * Created: 9/16/2021 5:24:29 PM
 *  Author: ahmed
 */ 
#define F_CPU 8000000


#include "LCD_CONFIG.h"
#include "DIO_INTERFACE.h"
#include <util/delay.h>
#include <stdlib.h>

/************************************************************************/
/*                              8 Bit mode                              */
/************************************************************************/

/* LCD_VoidSendCommand(0b00000001) */
void LCD_Void_8BitSendCommand(u8 command)
{
	DIO_VoidSetPinValue(RS,CONTROLPORT,LOW);
	DIO_VoidSetPinValue(RW,CONTROLPORT,LOW);
	DIO_VoidSetPortValue(DATAPORT,command);
	
	DIO_VoidSetPinValue(EN,CONTROLPORT,HIGH);
	_delay_ms(2);
	DIO_VoidSetPinValue(EN,CONTROLPORT,LOW);
}

void LCD_Void_8BitInit(void)
{
	DIO_VoidSetPinDirection(RS,CONTROLPORT,OUTPUT);
	DIO_VoidSetPinDirection(RW,CONTROLPORT,OUTPUT);
	DIO_VoidSetPinDirection(EN,CONTROLPORT,OUTPUT);
	
	DIO_VoidSetPortDirection(DATAPORT,OUTPUT);
	
	_delay_ms(30);
	LCD_Void_8BitSendCommand(FUNCTIONSET_8BIT);
	_delay_ms(2);
	LCD_Void_8BitSendCommand(DISPLAYON);
	_delay_ms(2);
	LCD_Void_8BitSendCommand(DISPLAYCLEAR);
	_delay_ms(15);
	LCD_Void_8BitSendCommand(ENTRYMODESET);
}

/* LCD_VoidSendChar('0')  */
void LCD_Void_8BitSendChar(u8 data)
{
	DIO_VoidSetPinValue(RS,CONTROLPORT,HIGH);
	DIO_VoidSetPinValue(RW,CONTROLPORT,LOW);
	DIO_VoidSetPortValue(DATAPORT,data);
	
	DIO_VoidSetPinValue(EN,CONTROLPORT,HIGH);
	_delay_ms(2);
	DIO_VoidSetPinValue(EN,CONTROLPORT,LOW);
}

void LCD_Void_8BitSendString(u8* PtrToString)
{
	u8 i=0;
	while(PtrToString[i] !=0)
	{
		LCD_Void_8BitSendChar(PtrToString[i]);
		i++;
	}
}

void LCD_Void_8BitSendNumber(u64 number)
{
		u8 arr_number[20];
		//itoa(number,arr_number,10);
		//LCD_Void_4BitSendString(arr_number);
		
		u8 count=0;
		while(number !=0)
		{
			arr_number[count] =number%10;
			count++;
			number /=10;
		}
		
		for (int i=count-1;i>=0;i--)
		{
			LCD_Void_8BitSendChar(arr_number[i]+48);
		}
}


/************************************************************************/
/*                              4 Bit mode                              */
/************************************************************************/

static u8 INIT_step_finished=0;

void LCD_Void_4BitSendCommand(u8 command)
{
	u8 COMMAND=command;
	DIO_VoidSetPinValue(RS,CONTROLPORT,LOW);
	DIO_VoidSetPinValue(RW,CONTROLPORT,LOW);
	
	COMMAND =(command) & (0XF0);
	
	if (UPPER_PINS_4BIT ==1)
	{
		DIO_VoidSetHigh4BitValue(DATAPORT,COMMAND);
	} 
	else
	{
		DIO_VoidSetLow4BitValue(DATAPORT,COMMAND);
	}
	
	DIO_VoidSetPinValue(EN,CONTROLPORT,HIGH);
	_delay_ms(2);
	DIO_VoidSetPinValue(EN,CONTROLPORT,LOW);
	
	if (INIT_step_finished==1)
	{
		COMMAND =(command<<4) & (0XF0);
		
		if (UPPER_PINS_4BIT ==1)
		{
			DIO_VoidSetHigh4BitValue(DATAPORT,COMMAND);
		}
		else
		{
			DIO_VoidSetLow4BitValue(DATAPORT,COMMAND);
		}
		
		DIO_VoidSetPinValue(EN,CONTROLPORT,HIGH);
		_delay_ms(2);
		DIO_VoidSetPinValue(EN,CONTROLPORT,LOW);
	}
	_delay_ms(2);
}

void LCD_Void_4BitInit(void)
{
	INIT_step_finished=0;
	DIO_VoidSetPinDirection(RS,CONTROLPORT,OUTPUT);
	DIO_VoidSetPinDirection(RW,CONTROLPORT,OUTPUT);
	DIO_VoidSetPinDirection(EN,CONTROLPORT,OUTPUT);
	
	if (UPPER_PINS_4BIT ==1)
	{
		DIO_VoidSetHigh4BitDirection(DATAPORT,0XF0);
	}
	else
	{
		DIO_VoidSetLow4BitDirection(DATAPORT,0X0F);
	}
	
	
	_delay_ms(30);
	LCD_Void_4BitSendCommand((FUNCTIONSET_4BIT>>4) & (0XF0));
	LCD_Void_4BitSendCommand((FUNCTIONSET_4BIT) & (0X0F0));
	LCD_Void_4BitSendCommand((FUNCTIONSET_4BIT<<4) & (0XF0));
	_delay_ms(2);
	LCD_Void_4BitSendCommand((DISPLAYON) & (0XF0));
	LCD_Void_4BitSendCommand((DISPLAYON<<4) & (0XF0));
	_delay_ms(2);
	LCD_Void_4BitSendCommand((DISPLAYCLEAR) & (0XF0));
	LCD_Void_4BitSendCommand((DISPLAYCLEAR<<4) & (0XF0));
	_delay_ms(15);
	LCD_Void_4BitSendCommand((ENTRYMODESET) & (0XF0));
	LCD_Void_4BitSendCommand((ENTRYMODESET<<4) & (0XF0));
	
	INIT_step_finished=1;
}


/* LCD_VoidSendChar('0')  */
void LCD_Void_4BitSendChar(u8 data)
{
	u8 DATA =data;
	DIO_VoidSetPinValue(RS,CONTROLPORT,HIGH);
	DIO_VoidSetPinValue(RW,CONTROLPORT,LOW);
	
	
	DATA =(data) & (0XF0);
	
	if (UPPER_PINS_4BIT ==1)
	{
		DIO_VoidSetHigh4BitValue(DATAPORT,DATA);
	}
	else
	{
		DIO_VoidSetLow4BitValue(DATAPORT,DATA);
	}
	
	DIO_VoidSetPinValue(EN,CONTROLPORT,HIGH);
	_delay_ms(2);
	DIO_VoidSetPinValue(EN,CONTROLPORT,LOW);
	
	DATA =(data<<4) & (0XF0);
	
	if (UPPER_PINS_4BIT ==1)
	{
		DIO_VoidSetHigh4BitValue(DATAPORT,DATA);
	}
	else
	{
		DIO_VoidSetLow4BitValue(DATAPORT,DATA);
	}
	
	DIO_VoidSetPinValue(EN,CONTROLPORT,HIGH);
	_delay_ms(2);
	DIO_VoidSetPinValue(EN,CONTROLPORT,LOW);
}

void LCD_Void_4BitSendString(u8* PtrToString)
{
	u8 i=0;
	while(PtrToString[i] !='\0')
	{
		LCD_Void_4BitSendChar(PtrToString[i]);
		i++;
	}
}

void LCD_Void_4BitSendNumber(u64 number)
{
	u8 arr_number[20];
	//itoa(number,arr_number,10);
	//LCD_Void_4BitSendString(arr_number);
	
	u8 count=0;
	while(number !=0)
	{
		arr_number[count] =number%10;
		count++;
		number /=10;
	}
	
	for (int i=count-1;i>=0;i--)
	{
		LCD_Void_4BitSendChar(arr_number[i]+48);
	}

}