/*
 * LCD_INT.h
 *
 * Created: 9/16/2021 5:24:12 PM
 *  Author: ahmed
 */ 

#include "STD_TYPES.h"

#ifndef LCD_INT_H_
#define LCD_INT_H_

/*******************************************************************************************/
/**************** 8Bit mode functions *************/

void LCD_Void_8BitInit(void);

void LCD_Void_8BitSendChar(u8 data);

void LCD_Void_8BitSendCommand(u8 command);

void LCD_Void_8BitSendString(u8* PtrToString);

void LCD_Void_8BitSendNumber(u64 number);

/*******************************************************************************************/
/**************** Bit mode functions *************/

void LCD_Void_4BitInit(void);

void LCD_Void_4BitSendChar(u8 data);

void LCD_Void_4BitSendCommand(u8 command);

void LCD_Void_4BitSendString(u8* PtrToString);

void LCD_Void_4BitSendNumber(u64 number);
/*******************************************************************************************/



#endif /* LCD_INT_H_ */