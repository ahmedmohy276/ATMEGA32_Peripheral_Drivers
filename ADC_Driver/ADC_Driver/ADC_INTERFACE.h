/*
 * ADC_INIT.h
 *
 * Created: 9/25/2021 7:48:04 PM
 *  Author: ahmed
 */ 

#include "STD_TYPES.h"

#ifndef ADC_INIT_H_
#define ADC_INIT_H_

typedef enum 
{
	INTERNAL_VREF_OFF,
	VREF_AVCC,
	REVERSED,
	INTERNAL_VREF_ON,
	
	PRESCALER_2,
	PRESCALER_4,
	PRESCALER_8,
	PRESCALER_16,
	PRESCALER_32,
	PRESCALER_64,
	PRESCALER_128,

	FREE_RUNNING,
	ANALOG_COMPARATOR,
	EXT_INTERRUPT_REQUIST_0,
	TIMER0_CTC,
	TIMER0_OVF,
	TIMER1_CTC_B,
	TIMER1_OVF,
	TIMER1_CAPTURE_EVENT,

	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,

	R_ADJUST_RESULT,
	L_ADJUST_RESULT,
	
	ENABLE_AUTO_TRIGGER,
	DISABLE_AUTO_TRIGGER,

	ENABLE_INTERRUPT,
	DISABLE_INTERRUPT,

	ANALOG_RESULT,
	DIGITAL_RESULT,

	ADCH_RESULT,
	ADCL_RESULT,
}ADC_Status;

void ADC_VoidInit(u8 channel,u8 Vref,u8 adjust_result,u8 trigger,u8 prescaler,u8 interrupt_status);

void ADC_VoidEnableADC(void);

void ADC_VoidSetADCChannel(u8 channel);

void ADC_VoidSetVref(u8 Vref);

void ADC_VoidSetAjustResultType(u8 adjust_result);

void ADC_VoidSetTriggerType(u8 trigger);

void ADC_VoidSetAutoTriggerSource(u8 auto_trigger_source);

void ADC_VoidSetPrescaler(u8 prescaler);

void ADC_VoidEnableDisableInterrupt(u8 interrupt_status);

void ADC_VoidStartConversion(void);

u8 ADC_VoidPollingADCResult_8BitDigitalResult(u8 result_type,u8 channel );

f32 ADC_VoidPollingADCResult_8BitAnalogResult(u8 result_type,u8 Vref,u8 channel );

u16 ADC_VoidPollingADCResult_10BitDigitalResult(u8 channel );

f32 ADC_VoidPollingADCResult_10BitAnalogResult(u8 Vref,u8 channel );

void ADC_SetCallBackFun(void (*PTRtoFunc) (void));

#endif /* ADC_INIT_H_ */