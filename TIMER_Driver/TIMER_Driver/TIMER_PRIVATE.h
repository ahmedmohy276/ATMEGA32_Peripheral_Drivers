/*
 * TIMER_REGISTERS.h
 *
 * Created: 9/30/2021 2:00:16 AM
 *  Author: Ahmed
 */ 


#ifndef TIMER_REGISTERS_H_
#define TIMER_REGISTERS_H_

#include "STD_TYPES.h"

void Timer_VoidSetWaveFormGenerationMode(u8 wave_form_mode,u8 timer);

void Timer_VoidSetPrescaler(u8 prescaler,u8 timer);


#define TCCR0_REG			  (*((volatile u8*) 0X53))

#define TCNT0_REG			  (*((volatile u8*) 0X52))

#define OCR0_REG			  (*((volatile u8*) 0X5C))

#define TIMSK_REG			  (*((volatile u8*) 0X59))

#define TIFR_REG			  (*((volatile u8*) 0X58))

#define SREG_REG			  (*((volatile u8*) 0X5F))

#define SFIOR_REG			  (*((volatile u8*) 0X50))

#define TCCR1A_REG			  (*((volatile u8*) 0X4F))

#define TCCR1B_REG			  (*((volatile u8*) 0X4E))

#define TCNT1H_REG			  (*((volatile u8*) 0X4D))

#define TCNT1L_REG			  (*((volatile u8*) 0X4C))

#define OCR1AH_REG			  (*((volatile u8*) 0X4B))

#define OCR1AL_REG			  (*((volatile u8*) 0X4A))

#define OCR1BH_REG			  (*((volatile u8*) 0X49))

#define OCR1BL_REG			  (*((volatile u8*) 0X48))

#define ICR1H_REG			  (*((volatile u8*) 0X47))

#define ICR1L_REG			  (*((volatile u8*) 0X46))

#define TCCR2_REG			  (*((volatile u8*) 0X45))

#define TCNT2_REG			  (*((volatile u8*) 0X44))

#define OCR2_REG			  (*((volatile u8*) 0X43))

#define ASSR_REG			  (*((volatile u8*) 0X42))



#endif /* TIMER_REGISTERS_H_ */