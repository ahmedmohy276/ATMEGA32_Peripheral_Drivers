/*
 * TIMER_PROG.c
 *
 * Created: 9/30/2021 2:00:57 AM
 *  Author: ahmed
 */ 

#include "TIMER_PRIVATE.h"
#include "TIMER_INTERFACE.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_INTERFACE.h"
#include <avr/interrupt.h>

u32 m_sec;
u32 u_sec;

u8 Timer;

u8 callback_flag;
u8 alarm_flag;
u8 ms_delay_flag;
u8 us_delay_flag;

void (*ptr_TIMER_0_OVF) (void);
void (*ptr_TIMER_0_COMP) (void);

void (*ptr_TIMER_1_OVF) (void);
void (*ptr_TIMER_1_COMP) (void);

void (*ptr_TIMER_2_OVF) (void);
void (*ptr_TIMER_2_COMP) (void);



void Timer_VoidInit(u8 timer,u8 wave_form_mode,u8 prescaler,u8 interrupt_status)
{
	Timer_VoidSetWaveFormGenerationMode(wave_form_mode,timer);
	
	Timer_VoidSetPrescaler(prescaler,timer);
	
	Timer_VoidInterruptStatus(timer,interrupt_status);
	
}


void Timer_VoidSetWaveFormGenerationMode(u8 wave_form_mode,u8 timer)
{
	if (timer==TIMER_0)
	{
		switch(wave_form_mode)
		{
			case NORMAL_MODE :
				CLEAR_Bit(TCCR0_REG,6);
				CLEAR_Bit(TCCR0_REG,3);
				break;
				
			case PWM_PHASE_CORRECT_MODE :
				SET_Bit(TCCR0_REG,6);
				CLEAR_Bit(TCCR0_REG,3);
				break;
				
			case CTC_MODE :
				CLEAR_Bit(TCCR0_REG,6);
				SET_Bit(TCCR0_REG,3);
				break;
				
			case FAST_PWM_MODE :
				SET_Bit(TCCR0_REG,6);
				SET_Bit(TCCR0_REG,3);
				break;
				
		}
	} 
	
	else if (timer==TIMER_2)
	{
		switch(wave_form_mode)
		{
			case NORMAL_MODE :
				CLEAR_Bit(TCCR2_REG,6);
				CLEAR_Bit(TCCR2_REG,3);
				break;
			
			case PWM_PHASE_CORRECT_MODE :
				SET_Bit(TCCR2_REG,6);
				CLEAR_Bit(TCCR2_REG,3);
				break;
			
			case CTC_MODE :
				CLEAR_Bit(TCCR2_REG,6);
				SET_Bit(TCCR2_REG,3);
				break;
			
			case FAST_PWM_MODE :
				SET_Bit(TCCR2_REG,6);
				SET_Bit(TCCR2_REG,3);
				break;
			
		}
	}
	
}

void Timer_VoidSetCompareMatchMode(u8 compare_match_mode,u8 timer)
{
	if (timer==TIMER_0)
	{
		if (compare_match_mode==DISCONNECT_OC0)
		{
			CLEAR_Bit(TCCR0_REG,4);
			CLEAR_Bit(TCCR0_REG,5);
		}
		else if ((compare_match_mode==TOGGLE_OC0) | (compare_match_mode==RESERVED))
		{
			SET_Bit(TCCR0_REG,4);
			CLEAR_Bit(TCCR0_REG,5);
		}
		else if ((compare_match_mode==CLEAR_OC0) | (compare_match_mode==NON_INVERTING_MODE))
		{
			CLEAR_Bit(TCCR0_REG,4);
			SET_Bit(TCCR0_REG,5);
		}
		else if ((compare_match_mode==SET_OC0) | (compare_match_mode==INVERTING_MODE))
		{
			SET_Bit(TCCR0_REG,4);
			SET_Bit(TCCR0_REG,5);
		}
	}
	
	else if(timer==TIMER_2)
	{
		if (compare_match_mode==DISCONNECT_OC0)
		{
			CLEAR_Bit(TCCR2_REG,4);
			CLEAR_Bit(TCCR2_REG,5);
		}
		else if ((compare_match_mode==TOGGLE_OC0) | (compare_match_mode==RESERVED))
		{
			SET_Bit(TCCR2_REG,4);
			CLEAR_Bit(TCCR2_REG,5);
		}
		else if ((compare_match_mode==CLEAR_OC0) | (compare_match_mode==NON_INVERTING_MODE))
		{
			CLEAR_Bit(TCCR2_REG,4);
			SET_Bit(TCCR2_REG,5);
		}
		else if ((compare_match_mode==SET_OC0) | (compare_match_mode==INVERTING_MODE))
		{
			SET_Bit(TCCR2_REG,4);
			SET_Bit(TCCR2_REG,5);
		}
	}
	
}

void Timer_VoidSetPrescaler(u8 prescaler,u8 timer)
{
	if (timer==TIMER_0)
	{
		switch(prescaler)
		{
			case NO_CLOCK_SOURCE :
				CLEAR_Bit(TCCR0_REG,0);
				CLEAR_Bit(TCCR0_REG,1);
				CLEAR_Bit(TCCR0_REG,2);
				break;
			
			case NO_PRESCALER :
				SET_Bit(TCCR0_REG,0);
				CLEAR_Bit(TCCR0_REG,1);
				CLEAR_Bit(TCCR0_REG,2);
				break;
			
			case PRESCALER_8 :
				CLEAR_Bit(TCCR0_REG,0);
				SET_Bit(TCCR0_REG,1);
				CLEAR_Bit(TCCR0_REG,2);
				break;
			
			case PRESCALER_64 :
				SET_Bit(TCCR0_REG,0);
				SET_Bit(TCCR0_REG,1);
				CLEAR_Bit(TCCR0_REG,2);
				break;
			
			case PRESCALER_256 :
				CLEAR_Bit(TCCR0_REG,0);
				CLEAR_Bit(TCCR0_REG,1);
				SET_Bit(TCCR0_REG,2);
				break;
			
			case PRESCALER_1024 :
				SET_Bit(TCCR0_REG,0);
				CLEAR_Bit(TCCR0_REG,1);
				SET_Bit(TCCR0_REG,2);
				break;
			
			case FALLING_EDGE_EXT_CLK :
				CLEAR_Bit(TCCR0_REG,0);
				SET_Bit(TCCR0_REG,1);
				SET_Bit(TCCR0_REG,2);
				break;
			
			case RISING_EDGE_EXT_CLK :
				SET_Bit(TCCR0_REG,0);
				SET_Bit(TCCR0_REG,1);
				SET_Bit(TCCR0_REG,2);
				break;
			
		}
	}
	
	else if (timer==TIMER_2)
	{
		switch(prescaler)
		{
			case NO_CLOCK_SOURCE :
				CLEAR_Bit(TCCR2_REG,0);
				CLEAR_Bit(TCCR2_REG,1);
				CLEAR_Bit(TCCR2_REG,2);
				break;
				
			case NO_PRESCALER :
				SET_Bit(TCCR2_REG,0);
				CLEAR_Bit(TCCR2_REG,1);
				CLEAR_Bit(TCCR2_REG,2);
				break;
				
			case PRESCALER_8 :
				CLEAR_Bit(TCCR2_REG,0);
				SET_Bit(TCCR2_REG,1);
				CLEAR_Bit(TCCR2_REG,2);
				break;
				
			case PRESCALER_32 :
				SET_Bit(TCCR2_REG,0);
				SET_Bit(TCCR2_REG,1);
				CLEAR_Bit(TCCR0_REG,2);
				break;
				
			case PRESCALER_64 :
				CLEAR_Bit(TCCR2_REG,0);
				CLEAR_Bit(TCCR2_REG,1);
				SET_Bit(TCCR2_REG,2);
				break;
				
			case PRESCALER_128 :
				SET_Bit(TCCR2_REG,0);
				CLEAR_Bit(TCCR2_REG,1);
				SET_Bit(TCCR2_REG,2);
				break;
				
			case PRESCALER_256 :
				CLEAR_Bit(TCCR2_REG,0);
				SET_Bit(TCCR2_REG,1);
				SET_Bit(TCCR2_REG,2);
				break;
				
			case PRESCALER_1024 :
				SET_Bit(TCCR2_REG,0);
				SET_Bit(TCCR2_REG,1);
				SET_Bit(TCCR2_REG,2);
				break;
				
		}
	}
	
}

void Timer_VoidInterruptStatus(u8 timer,u8 interrupt_status)
{
	switch(timer)
	{
		case TIMER_0 :
			switch (interrupt_status)
			{
				case COMPARE_MATCH_INT_EN :
					SET_Bit(TIMSK_REG,1);
					/*****Global interrupt enable************/
					SET_Bit(SREG_REG,7);
					break;
					
				case COMPARE_MATCH_INT_DISABLE :
					CLEAR_Bit(TIMSK_REG,1);
					break;
					
				case OVERFLOW_INT_EN :
					SET_Bit(TIMSK_REG,0);
					/*****Global interrupt enable************/
					SET_Bit(SREG_REG,7);
					break;
					
				case OVERFLOW_INT_DISABLE :
					CLEAR_Bit(TIMSK_REG,0);
					break;
			}
			break;
			
		case TIMER_2 :
			switch (interrupt_status)
			{
				case COMPARE_MATCH_INT_EN :
				SET_Bit(TIMSK_REG,7);
				/*****Global interrupt enable************/
				SET_Bit(SREG_REG,7);
				break;
				
				case COMPARE_MATCH_INT_DISABLE :
				CLEAR_Bit(TIMSK_REG,7);
				break;
				
				case OVERFLOW_INT_EN :
				SET_Bit(TIMSK_REG,6);
				/*****Global interrupt enable************/
				SET_Bit(SREG_REG,7);
				break;
				
				case OVERFLOW_INT_DISABLE :
				CLEAR_Bit(TIMSK_REG,6);
				break;
			}
			break;
	}
	
}

void Timer_VoidPWMGeneration(u8 timer,u8 duty_cycle,u8 PWM_mode,u8 OC0_status,u8 prescaler)
{
	u8 ocr_value;
	Timer_VoidSetWaveFormGenerationMode(PWM_mode,timer);
	Timer_VoidSetCompareMatchMode(OC0_status,timer);
	Timer_VoidSetPrescaler(prescaler,timer);
	switch(timer)
	{
		case TIMER_0 :
			//set pin OC0 as output
			DIO_VoidSetPinDirection(3,portB,OUTPUT);
			if (PWM_mode==FAST_PWM_MODE)
			{
				ocr_value =(duty_cycle*255)/100;
				Timer_VoidSetOCRValue(ocr_value,timer);
			} 
			else if (PWM_mode==PWM_PHASE_CORRECT_MODE)
			{
				ocr_value =(duty_cycle*510)/100;
				Timer_VoidSetOCRValue(ocr_value,timer);
			}
			
			break;
		
		case TIMER_2 :
			//set pin OC2 as output
			DIO_VoidSetPinDirection(7,portD,OUTPUT);
			if (PWM_mode==FAST_PWM_MODE)
			{
				ocr_value =(duty_cycle*256)/100;
				Timer_VoidSetOCRValue(ocr_value,timer);
			}
			else if (PWM_mode==PWM_PHASE_CORRECT_MODE)
			{
				ocr_value =(duty_cycle*512)/100;
				Timer_VoidSetOCRValue(ocr_value,timer);
			}
			
			break;
		
	}
}

void Timer_VoidSetTCNTValue(u8 TCNT_value,u8 timer)
{
	switch(timer)
	{
		case TIMER_0 :
			TCNT0_REG=TCNT_value;
			break;

		case TIMER_2 :
			TCNT2_REG=TCNT_value;
			break;
			
	}
}

void Timer_VoidSetOCRValue(u8 OCR_value,u8 timer)
{
	switch(timer)
	{
		case TIMER_0 :
			OCR0_REG=OCR_value;
			break;
		
		case TIMER_2 :
			OCR2_REG=OCR_value;
			break;
		
	}
}


void Timer_VoidSetCallBackFunction(void (*ptrToFunction) (void),u8 interrupt_type,u8 timer)
{
	callback_flag=1;
	Timer=timer;
	switch(timer)
	{
		case TIMER_0 :
			if (interrupt_type==COMPARE_MATCH_INT_EN)
			{
				ptr_TIMER_0_COMP=ptrToFunction;
			}
			else if (interrupt_type==OVERFLOW_INT_EN)
			{
				ptr_TIMER_0_OVF=ptrToFunction;
			}
			break;

		case TIMER_2 :
			if (interrupt_type==COMPARE_MATCH_INT_EN)
			{
				ptr_TIMER_2_COMP=ptrToFunction;
			}
			else if (interrupt_type==OVERFLOW_INT_EN)
			{
				ptr_TIMER_0_OVF=ptrToFunction;
			}
			break;
			
	}
}

void Timer_VoidSetAlarm(u32 time_ms,u8 timer,void (*ptrToFunction) (void))
{   
	/************************************************************************/
	/*             (OCR+1)*(1/8000000)*64=1ms------->> OCR=124;             */
	/************************************************************************/
	Timer=timer;
	alarm_flag=1;
	m_sec=time_ms;
	Timer_VoidInit(timer,CTC_MODE,PRESCALER_64,COMPARE_MATCH_INT_EN);
	//Timer_VoidSetWaveFormGenerationMode(CTC_MODE,timer);
	Timer_VoidSetCompareMatchMode(DISCONNECT_OC0,timer);
	//Timer_VoidSetPrescaler(PRESCALER_64,timer);
	//Timer_VoidInterruptStatus(timer,COMPARE_MATCH_INT_EN);
	Timer_VoidSetOCRValue(124,timer);
	
	switch(timer)
	{
		case TIMER_0 :
			ptr_TIMER_0_COMP=ptrToFunction;
			break;
		
		case TIMER_2 :
			ptr_TIMER_2_COMP=ptrToFunction;
			break;
			
	}
}

void delay_ms(u32 time_ms)
{
	/************************************************************************/
	/*             (OCR+1)*(1/8000000)*64=1ms------->> OCR=124;             */
	/************************************************************************/
	ms_delay_flag=1;
	m_sec=time_ms;
	Timer_VoidInit(TIMER_0,CTC_MODE,PRESCALER_64,COMPARE_MATCH_INT_EN);
	Timer_VoidSetCompareMatchMode(DISCONNECT_OC0,TIMER_0);
	Timer_VoidSetOCRValue(124,TIMER_0);
	while(ms_delay_flag==1);
	TCCR0_REG = 0x00;
}

void delay_us(u32 time_us)
{
	/************************************************************************/
	/*             (OCR+1)*(1/8000000)=1us------->> OCR=7;             */
	/************************************************************************/
	us_delay_flag=1;
	u_sec=time_us;
	Timer_VoidInit(TIMER_2,CTC_MODE,PRESCALER_64,COMPARE_MATCH_INT_EN);
	Timer_VoidSetCompareMatchMode(DISCONNECT_OC0,TIMER_2);
	Timer_VoidSetOCRValue(7,TIMER_2);
	while(us_delay_flag==1);
	TCCR2_REG = 0x00;
	
}

 
ISR(TIMER0_COMP_vect)
{
	static u32 count_0=0;
	static u32 ms_count_0=0;
	
	if (Timer==TIMER_0 && alarm_flag==1)
	{
		if (count_0==m_sec)
		{
			ptr_TIMER_0_COMP();
			count_0=0;
		}
		else
		{
			count_0++;
		}
	}
	
	
	if (ms_delay_flag==1)
	{
		if (ms_count_0==m_sec)
		{
			ms_delay_flag=0;
			ms_count_0=0;
		}
		else
		{
			ms_count_0++;
		}
	}
	
	if (Timer==TIMER_0 && callback_flag==1)
	{
		ptr_TIMER_0_COMP();
	}
	
}

ISR(TIMER0_OVF_vect)
{
	ptr_TIMER_0_OVF();
}


ISR(TIMER2_COMP_vect)
{
	static u32 count_2=0;
	static u32 us_count_2=0;
	if (Timer==TIMER_2 && alarm_flag==1)
	{
		if (count_2==m_sec)
		{
			ptr_TIMER_2_COMP();
			count_2=0;
		}
		else
		{
			count_2++;
		}
	}
	
	if (us_delay_flag==1)
	{
		if (us_count_2==u_sec)
		{
			us_delay_flag=0;
			us_count_2=0;
		}
		else
		{
			us_count_2++;
		}
	}
	
	if (Timer==TIMER_2 && callback_flag==1)
	{
		ptr_TIMER_2_COMP();
	}
}

ISR(TIMER2_OVF_vect)
{
	ptr_TIMER_2_OVF();
}