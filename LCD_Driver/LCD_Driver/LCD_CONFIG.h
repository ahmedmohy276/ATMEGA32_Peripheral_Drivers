/*
 * LCD_CONFIG.h
 *
 * Created: 9/17/2021 2:25:51 AM
 *  Author: ahmed
 */ 

#include "DIO_INTERFACE.h"

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_




#define RS  0
#define RW  1
#define EN  2

#define CONTROLPORT portD
#define DATAPORT    portD

#define UPPER_PINS_4BIT        1

#define FUNCTIONSET_8BIT   0b00111000
#define FUNCTIONSET_4BIT   0b001000101000
#define DISPLAYON          0b00001110
#define DISPLAYOFF         0b00001010
#define DISPLAYCLEAR       0b00000001
#define ENTRYMODESET       0b00000010


#endif /* LCD_CONFIG_H_ */