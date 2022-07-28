/*
 * TIMER_INTERFACE.h
 *
 * Created: 9/30/2021 2:00:40 AM
 *  Author: ahmed
 */ 


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#include "STD_TYPES.h"

typedef enum 
{
	TIMER_0,
	TIMER_2,
	/**************Waveform Generation Mode****************/
	NORMAL_MODE,
	PWM_PHASE_CORRECT_MODE,
	CTC_MODE,
	FAST_PWM_MODE,
	/*********Compare Output(CTC) Mode non-PWM Mode**************/
	DISCONNECT_OC0,
	TOGGLE_OC0,
	CLEAR_OC0,
	SET_OC0,
	/***********Compare Output(CTC) Mode Fast PWM Mode************/
	/***********Compare Output Mode, Phase Correct PWM Mode************/
	//DISCONNECT_OC0,
	RESERVED,
	NON_INVERTING_MODE,
	INVERTING_MODE,
	/************************Prescaler*****************************/
	NO_CLOCK_SOURCE,
	NO_PRESCALER,
	PRESCALER_8,
	PRESCALER_32,
	PRESCALER_64,
	PRESCALER_128,
	PRESCALER_256,
	PRESCALER_1024,
	FALLING_EDGE_EXT_CLK,
	RISING_EDGE_EXT_CLK,

	COMPARE_MATCH_INT_EN,
	OVERFLOW_INT_EN,
	COMPARE_MATCH_INT_DISABLE,
	OVERFLOW_INT_DISABLE,
}TIMER_Status;


#define FOSC                                8000000


void Timer_VoidInit(u8 timer,u8 wave_form_mode,u8 prescaler,u8 interrupt_status);

void Timer_VoidSetCompareMatchMode(u8 compare_match_mode,u8 timer);

void Timer_VoidInterruptStatus(u8 timer,u8 interrupt_status);

void Timer_VoidPWMGeneration(u8 timer,u8 duty_cycle,u8 PWM_mode,u8 OC0_status,u8 prescaler);

void Timer_VoidSetCallBackFunction(void (*ptrToFunction) (void),u8 interrupt_type,u8 timer);

void Timer_VoidSetTCNTValue(u8 TCNT_value,u8 timer);

void Timer_VoidSetOCRValue(u8 OCR_value,u8 timer);

void delay_ms(u32 time_ms);

void delay_us(u32 time_us);

void Timer_VoidSetAlarm(u32 time_ms,u8 timer,void (*ptrToFunction) (void));


#endif /* TIMER_INTERFACE_H_ */