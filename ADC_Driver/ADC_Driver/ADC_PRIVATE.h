/*
 * ADC_REGISTERS.h
 *
 * Created: 9/26/2021 10:42:00 PM
 *  Author: ahmed
 */ 


#ifndef ADC_REGISTERS_H_
#define ADC_REGISTERS_H_



void ADC_VoidEnableADC(void);

void ADC_VoidSetADCChannel(u8 channel);

void ADC_VoidSetVref(u8 Vref);

void ADC_VoidSetAjustResultType(u8 adjust_result);

void ADC_VoidSetTriggerType(u8 trigger);

void ADC_VoidSetPrescaler(u8 prescaler);

void ADC_VoidEnableDisableInterrupt(u8 interrupt_status);



#define ADMUX_REG			  (*((volatile u8*) 0X27))

#define ADCSRA_REG			  (*((volatile u8*) 0X26))

#define ADCH_REG			  (*((volatile u8*) 0X25))

#define ADCL_REG			  (*((volatile u8*) 0X24))

#define SFIOR_REG			  (*((volatile u8*) 0X50))

#define SREG_REG			  (*((volatile u8*) 0X5F))


#endif /* ADC_REGISTERS_H_ */