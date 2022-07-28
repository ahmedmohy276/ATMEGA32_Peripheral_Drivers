/*
 * KEYPAD_PROG.c
 *
 * Created: 9/18/2021 5:31:29 PM
 *  Author: ahmed
 */ 

#define F_CPU 8000000
#include <util/delay.h>
#include "DIO_INTERFACE.h"
#include "DIO_PRIVATE.h"
#include "KEYPAD_CONFIG.h"



//u8 arrkeypadvalue[COL][ROW]={ {'1','4','7','*'},{'2','5','8','0'},{'3','6','9','#'} };
static u8 arrkeypadvalue[ROW][COL]={	{'7','8','9','/'},
										{'4','5','6','*'},
										{'1','2','3','-'},
										{' ','0','=','+'}	};

void Keypad_VoidInit(void)
{
	DIO_VoidSetPinDirection(R0,KEYPADPORT,INPUT);
	DIO_VoidSetPinDirection(R1,KEYPADPORT,INPUT);
	DIO_VoidSetPinDirection(R2,KEYPADPORT,INPUT);
	DIO_VoidSetPinDirection(R3,KEYPADPORT,INPUT);
	
	DIO_VoidSetPinDirection(C0,KEYPADPORT,OUTPUT);
	DIO_VoidSetPinDirection(C1,KEYPADPORT,OUTPUT);
	DIO_VoidSetPinDirection(C2,KEYPADPORT,OUTPUT);
	DIO_VoidSetPinDirection(C3,KEYPADPORT,OUTPUT);
	
	DIO_VoidSetPortValue(KEYPADPORT,0xFF);
}

u8 Keypad_U8_GetPressed(void)
{
	u8 keypad_pressed_flag=0;
	volatile u8 row_count=ROW_INIT;
	volatile u8 col_count=COL_INIT;
	u8 result=0;
	while(1)
	{
		for (col_count=COL_INIT; col_count<COL_END; col_count++)
		{
			/*************Activate column*****************/
			DIO_VoidSetPinValue(col_count,KEYPADPORT,LOW);
			
			for (row_count=ROW_INIT; row_count<ROW_END; row_count++)
			{
				if (DIO_U8GetPinValue(row_count,KEYPADPORT) == LOW)
				{
					result=arrkeypadvalue[row_count-ROW_INIT][col_count-COL_INIT];
					
					while(DIO_U8GetPinValue(row_count,KEYPADPORT) == LOW);  //stuck till button is not pressed (single press)
					
					_delay_ms(10); //delay to avoid bouncing
					
					keypad_pressed_flag=1;
					//return result;
					
				}
			}
			
			/*************Deactivate column*****************/
			DIO_VoidSetPinValue(col_count,KEYPADPORT,HIGH);
		}
		
		if (keypad_pressed_flag==1)
		{
			break;
		}
	}
	
	return result;
}
