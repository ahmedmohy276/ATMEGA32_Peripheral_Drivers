/*
 * ADC_Driver.c
 *
 * Created: 9/25/2021 6:58:51 PM
 * Author : ahmed
 */ 
#define F_CPU 8000000

//#include <avr/io.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "ADC_INTERFACE.h"
#include "LCD_CONFIG.h"
#include "LCD_INTERFACE.h"
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	LCD_Void_4BitInit();
	u16 result=0;
	//u8 result_8;
	DIO_VoidSetPortDirection(portC,OUTPUT);
	//DIO_VoidSetPinDirection(0,portD,OUTPUT);
	//DIO_VoidSetPinDirection(1,portD,OUTPUT);
	ADC_VoidInit(ADC0,VREF_AVCC,R_ADJUST_RESULT,DISABLE_AUTO_TRIGGER,PRESCALER_64,DISABLE_INTERRUPT);
	_delay_ms(100);
    while (1) 
    {
		LCD_Void_4BitSendCommand(DISPLAYCLEAR);
		LCD_Void_4BitSendString((u8*)"ADC result1 = ");
		result=ADC_VoidPollingADCResult_10BitDigitalResult(ADC0);
		LCD_Void_4BitSendNumber(result);
		//DIO_VoidSetPortValue(portC,(u8)result);
		//DIO_VoidSetPortValue(portD,(result>>8) & (0x02));
		
		_delay_ms(1000);
		
		LCD_Void_4BitSendCommand(DISPLAYCLEAR);
		LCD_Void_4BitSendString((u8*)"ADC result2 = ");
		result=ADC_VoidPollingADCResult_10BitDigitalResult(ADC1);
		LCD_Void_4BitSendNumber(result);
		//DIO_VoidSetPortValue(portC,(u8)result);
		//DIO_VoidSetPortValue(portD,result>>8);
		_delay_ms(1000);
		
		/*result=ADC_VoidPollingADCResult_10BitDigitalResult(5,ADC0);
		DIO_VoidSetPortValue(portC,result);
		DIO_VoidSetPortValue(portD,result>>8);
		_delay_ms(1000);
		
		result=ADC_VoidPollingADCResult_10BitDigitalResult(5,ADC1);
		DIO_VoidSetPortValue(portC,result);
		DIO_VoidSetPortValue(portD,result>>8);
		_delay_ms(1000);*/
    }
}

