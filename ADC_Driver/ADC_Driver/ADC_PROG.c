/*
 * ADC_PROG.c
 *
 * Created: 9/25/2021 7:48:19 PM
 *  Author: Ahmed
 */ 
#include "STD_TYPES.h"
#include "ADC_PRIVATE.h"
#include "ADC_INTERFACE.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 8000000


void (*ptr) (void);          //global pointer to function 

void ADC_VoidEnableADC(void)
{
	SET_Bit(ADCSRA_REG,7);
}

void ADC_VoidSetADCChannel(u8 channel)
{
	switch(channel)
	{
		case ADC0 :
			CLEAR_Bit(ADMUX_REG,0);
			CLEAR_Bit(ADMUX_REG,1);
			CLEAR_Bit(ADMUX_REG,2);
			CLEAR_Bit(ADMUX_REG,3);
			CLEAR_Bit(ADMUX_REG,4);
			break;
		
		case ADC1 :
			SET_Bit(ADMUX_REG,0);
			CLEAR_Bit(ADMUX_REG,1);
			CLEAR_Bit(ADMUX_REG,2);
			CLEAR_Bit(ADMUX_REG,3);
			CLEAR_Bit(ADMUX_REG,4);
			break;
			
		case ADC2 :
			CLEAR_Bit(ADMUX_REG,0);
			SET_Bit(ADMUX_REG,1);
			CLEAR_Bit(ADMUX_REG,2);
			CLEAR_Bit(ADMUX_REG,3);
			CLEAR_Bit(ADMUX_REG,4);
			break;
			
		case ADC3 :
			SET_Bit(ADMUX_REG,0);
			SET_Bit(ADMUX_REG,1);
			CLEAR_Bit(ADMUX_REG,2);
			CLEAR_Bit(ADMUX_REG,3);
			CLEAR_Bit(ADMUX_REG,4);
			break;
			
		case ADC4 :
			CLEAR_Bit(ADMUX_REG,0);
			CLEAR_Bit(ADMUX_REG,1);
			SET_Bit(ADMUX_REG,2);
			CLEAR_Bit(ADMUX_REG,3);
			CLEAR_Bit(ADMUX_REG,4);
			break;
			
		case ADC5:
			SET_Bit(ADMUX_REG,0);
			CLEAR_Bit(ADMUX_REG,1);
			SET_Bit(ADMUX_REG,2);
			CLEAR_Bit(ADMUX_REG,3);
			CLEAR_Bit(ADMUX_REG,4);
			break;
			
		case ADC6 :
			CLEAR_Bit(ADMUX_REG,0);
			SET_Bit(ADMUX_REG,1);
			SET_Bit(ADMUX_REG,2);
			CLEAR_Bit(ADMUX_REG,3);
			CLEAR_Bit(ADMUX_REG,4);
			break;
			
		case ADC7 :
			SET_Bit(ADMUX_REG,0);
			SET_Bit(ADMUX_REG,1);
			SET_Bit(ADMUX_REG,2);
			CLEAR_Bit(ADMUX_REG,3);
			CLEAR_Bit(ADMUX_REG,4);
			break;
			
	}
}



void ADC_VoidSetVref(u8 Vref)
{
	switch(Vref)
	{
		case INTERNAL_VREF_OFF :
			CLEAR_Bit(ADMUX_REG,6);
			CLEAR_Bit(ADMUX_REG,7);
			break;
			
		case VREF_AVCC :
			SET_Bit(ADMUX_REG,6);
			CLEAR_Bit(ADMUX_REG,7);
			break;
			
		case REVERSED :
			CLEAR_Bit(ADMUX_REG,6);
			SET_Bit(ADMUX_REG,7);
			break;
			
		case INTERNAL_VREF_ON :
			SET_Bit(ADMUX_REG,6);
			SET_Bit(ADMUX_REG,7);
			break;
	}
}



void ADC_VoidSetAjustResultType(u8 adjust_result)
{
	switch(adjust_result)
	{
		case R_ADJUST_RESULT :
			CLEAR_Bit(ADMUX_REG,5);
			break;
		
		case L_ADJUST_RESULT :
			SET_Bit(ADMUX_REG,5);
			break;
			
	}
}



void ADC_VoidSetTriggerType(u8 trigger)
{
	switch(trigger)
	{
		case ENABLE_AUTO_TRIGGER :
			SET_Bit(ADCSRA_REG,5);;
			break;
			
		case DISABLE_AUTO_TRIGGER :
			CLEAR_Bit(ADCSRA_REG,5);
			break;
			
	}
}



void ADC_VoidSetAutoTriggerSource(u8 auto_trigger_source)
{
	switch(auto_trigger_source)
	{
		case FREE_RUNNING :
			CLEAR_Bit(SFIOR_REG,5);
			CLEAR_Bit(SFIOR_REG,6);
			CLEAR_Bit(SFIOR_REG,7);
			break;
			
		case ANALOG_COMPARATOR :
			SET_Bit(SFIOR_REG,5);
			CLEAR_Bit(SFIOR_REG,6);
			CLEAR_Bit(SFIOR_REG,7);
			break;
			
		case EXT_INTERRUPT_REQUIST_0 :
			CLEAR_Bit(SFIOR_REG,5);
			SET_Bit(SFIOR_REG,6);
			CLEAR_Bit(SFIOR_REG,7);
			break;
			
		case TIMER0_CTC :
			SET_Bit(SFIOR_REG,5);
			SET_Bit(SFIOR_REG,6);
			CLEAR_Bit(SFIOR_REG,7);
			break;
			
		case TIMER0_OVF :
			CLEAR_Bit(SFIOR_REG,5);
			CLEAR_Bit(SFIOR_REG,6);
			SET_Bit(SFIOR_REG,7);
			break;
			
		case TIMER1_CTC_B :
			SET_Bit(SFIOR_REG,5);
			CLEAR_Bit(SFIOR_REG,6);
			SET_Bit(SFIOR_REG,7);
			break;
			
		case TIMER1_OVF :
			CLEAR_Bit(SFIOR_REG,5);
			SET_Bit(SFIOR_REG,6);
			SET_Bit(SFIOR_REG,7);
			break;
			
		case TIMER1_CAPTURE_EVENT :
			SET_Bit(SFIOR_REG,5);
			SET_Bit(SFIOR_REG,6);
			SET_Bit(SFIOR_REG,7);
			break;
			
	}
}



void ADC_VoidSetPrescaler(u8 prescaler)
{
	switch(prescaler)
	{
		case PRESCALER_2 :
			CLEAR_Bit(ADCSRA_REG,0);
			CLEAR_Bit(ADCSRA_REG,1);
			CLEAR_Bit(ADCSRA_REG,2);
			break;
			
		case PRESCALER_4 :
			CLEAR_Bit(ADCSRA_REG,0);
			SET_Bit(ADCSRA_REG,1);
			CLEAR_Bit(ADCSRA_REG,2);
			break;
			
		case PRESCALER_8 :
			SET_Bit(ADCSRA_REG,0);
			SET_Bit(ADCSRA_REG,1);
			CLEAR_Bit(ADCSRA_REG,2);
			break;
			
		case PRESCALER_16 :
			CLEAR_Bit(ADCSRA_REG,0);
			CLEAR_Bit(ADCSRA_REG,1);
			SET_Bit(ADCSRA_REG,2);
			break;
			
		case PRESCALER_32 :
			SET_Bit(ADCSRA_REG,0);
			CLEAR_Bit(ADCSRA_REG,1);
			SET_Bit(ADCSRA_REG,2);
			break;
			
		case PRESCALER_64 :
			CLEAR_Bit(ADCSRA_REG,0);
			SET_Bit(ADCSRA_REG,1);
			SET_Bit(ADCSRA_REG,2);
			break;
			
		case PRESCALER_128 :
			SET_Bit(ADCSRA_REG,0);
			SET_Bit(ADCSRA_REG,1);
			SET_Bit(ADCSRA_REG,2);
			break;
			
	}
}



void ADC_VoidEnableDisableInterrupt(u8 EN_DIS_interrupt)
{
	switch(EN_DIS_interrupt)
	{
		case ENABLE_INTERRUPT :
			SET_Bit(ADCSRA_REG,3);
			SET_Bit(SREG_REG,7);
			break;
			
		case DISABLE_INTERRUPT :
			CLEAR_Bit(ADCSRA_REG,3);
			break;
			
	}
	
}


void ADC_VoidInit(u8 channel,u8 Vref,u8 adjust_result,u8 trigger,u8 prescaler,u8 interrupt_status)
{
	ADC_VoidEnableADC();

	ADC_VoidSetADCChannel(channel);

	ADC_VoidSetVref(Vref);

	ADC_VoidSetAjustResultType(adjust_result);

	ADC_VoidSetTriggerType(trigger);

	ADC_VoidSetPrescaler(prescaler);

	ADC_VoidEnableDisableInterrupt(interrupt_status);
}


void ADC_SetCallBackFun(void (*PTRtoFunc) (void))
{
	ptr=PTRtoFunc;
}



void ADC_VoidStartConversion(void)
{
	SET_Bit(ADCSRA_REG,6);
}

u8 ADC_VoidPollingADCResult_8BitDigitalResult(u8 result_type,u8 channel )
{
	//make channel as input
	DIO_VoidSetPinDirection(channel,portA,INPUT);
	u8 result=0;
	ADC_VoidSetADCChannel(channel);
	ADC_VoidStartConversion();
	
	while(GET_Bit(ADCSRA_REG,4)==0);  //wait untill conversion complete
	SET_Bit(ADCSRA_REG,4);			//clear ADC interrupt flag
	
	if (result_type==ADCH_RESULT)
	{
		result =ADCH_REG;   //return the digital result that matches the analog voltages
	}
	else if (result_type==ADCL_RESULT)
	{
		result =ADCL_REG;   //return the digital result that matches the analog voltages
	}
	
	return result;
}




u16 ADC_VoidPollingADCResult_10BitDigitalResult(u8 channel)
{
	//make channel as input
	DIO_VoidSetPinDirection(channel,portA,INPUT);
	u16 result=0;
	ADC_VoidSetADCChannel(channel);
	ADC_VoidStartConversion();
	
	
	while(GET_Bit(ADCSRA_REG,4)==0);  //wait untill conversion complete
	SET_Bit(ADCSRA_REG,4);			//clear ADC interrupt flag
	_delay_us(20);
	
	result=(u8)ADCL_REG;
	result |=(ADCH_REG<<8);  //return the digital result that matches the analog voltage
		
	return result;
}


f32 ADC_VoidPollingADCResult_8BitAnalogResult(u8 result_type,u8 Vref,u8 channel )
{
	//make channel as input
	DIO_VoidSetPinDirection(channel,portA,INPUT);
	f32 result=0;
	ADC_VoidSetADCChannel(channel);
	ADC_VoidStartConversion();
	
	while(GET_Bit(ADCSRA_REG,4)==0);  //wait untill conversion complete
	SET_Bit(ADCSRA_REG,4);			//clear ADC interrupt flag
	
	if (result_type==ADCH_RESULT)
	{
		result = (ADCH_REG/1023.0) *Vref;   //convert the digital result to analog voltage and return it
	}
	else if (result_type==ADCL_RESULT)
	{
		result = (ADCL_REG/1023.0) *Vref;   //convert the digital result to analog voltage and return it
	}
	
	return result;
}


f32 ADC_VoidPollingADCResult_10BitAnalogResult(u8 Vref,u8 channel )
{
	//make channel as input
	DIO_VoidSetPinDirection(channel,portA,INPUT);
	u16 digital_result=0;
	f32 result=0;
	ADC_VoidSetADCChannel(channel);
	ADC_VoidStartConversion();
	
	while(GET_Bit(ADCSRA_REG,4)==0);  //wait untill conversion complete
	SET_Bit(ADCSRA_REG,4);			//clear ADC interrupt flag
	
	digital_result=ADCL_REG;
	digital_result |=(ADCH_REG<<8);
	result =(digital_result/1023.0) *Vref;  //convert the digital result to analog voltage and return it
	
	return result;
}


ISR(ADC_vect)
{
	ptr();
}