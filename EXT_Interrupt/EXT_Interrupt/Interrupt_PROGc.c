/*
 * Interrupt_PROGc.c
 *
 * Created: 9/25/2021 3:03:39 AM
 *  Author: ahmed
 */ 
#include "STD_TYPES.h"
#include "Interrupt_INTERFACE.h"
#include <avr/interrupt.h>
#include "Interrupt_PPRIVATE.h"
#include "BIT_MATH.h"

void (*INT0_ptr) (void);
void (*INT1_ptr) (void);
void (*INT2_ptr) (void);

void Interrupt_VoidInterruptActivate(u8 INT_Index,u8 INT_Type)
{
	/******glopal interrupt enable****/
	SREG_REG |=(1<<7);
	
	switch(INT_Index)
	{
		case INT_0 :
			/***INT0 enable****/
			GICR_REG |=(1<<6);
			if (INT_Type==LOW_LEVEL)
			{
				CLEAR_Bit(MCUCR_REG,0);
				CLEAR_Bit(MCUCR_REG,1);
			}
			else if (INT_Type==ANY_CHANGE)
			{
				SET_Bit(MCUCR_REG,0);
				CLEAR_Bit(MCUCR_REG,1);
			}
			else if (INT_Type==FALLING_EDGE)
			{
				SET_Bit(MCUCR_REG,1);
				CLEAR_Bit(MCUCR_REG,0);
			}
			else if (INT_Type==RISING_EDGE)
			{
				SET_Bit(MCUCR_REG,0);
				SET_Bit(MCUCR_REG,1);
			}
		case INT_1 :
			/***INT1 enable****/
			GICR_REG |=(1<<7);
			if (INT_Type==LOW_LEVEL)
			{
				CLEAR_Bit(MCUCR_REG,2);
				CLEAR_Bit(MCUCR_REG,3);
			}
			else if (INT_Type==ANY_CHANGE)
			{
				SET_Bit(MCUCR_REG,2);
				CLEAR_Bit(MCUCR_REG,3);
			}
			else if (INT_Type==FALLING_EDGE)
			{
				SET_Bit(MCUCR_REG,3);
				CLEAR_Bit(MCUCR_REG,2);
			}
			else if (INT_Type==RISING_EDGE)
			{
				SET_Bit(MCUCR_REG,2);
				SET_Bit(MCUCR_REG,3);
			}
			
		case INT_2 :
			/***INT2 enable****/
			GICR_REG |=(1<<5);
			if (INT_Type==FALLING_EDGE)
			{
				CLEAR_Bit(MCUCSR_REG,6);
			}
			else if (INT_Type==RISING_EDGE)
			{
				SET_Bit(MCUCSR_REG,6);
			}
	}
}

void Interrupt_SetCallBackFunction(void (*ptrToFun) (void),u8 INT_index)
{
	switch(INT_index)
	{
		case INT_0 :
			INT0_ptr=ptrToFun;
		
		case INT_1 :
			INT1_ptr=ptrToFun;
		
		case INT_2 :
			INT2_ptr=ptrToFun;
	}
}


ISR(INT0_vect)
{
	INT0_ptr();
}

ISR(INT1_vect)
{
	INT1_ptr();
}

ISR(INT2_vect)
{
	INT2_ptr();
}