/*
 * Interrupt_INIT.h
 *
 * Created: 9/25/2021 3:03:21 AM
 *  Author: ahmed
 */ 


#ifndef INTERRUPT_INIT_H_
#define INTERRUPT_INIT_H_


typedef enum
{
	FALLING_EDGE,
	RISING_EDGE, 
	ANY_CHANGE,
	LOW_LEVEL,
	INT_0,
	INT_1,
	INT_2,
}INT_Status;


void Interrupt_VoidInterruptActivate(u8 INT_Index,u8 INT_Type);

void Interrupt_SetCallBackFunction(void (*ptrToFun) (void),u8 INT_index);


#endif /* INTERRUPT_INIT_H_ */