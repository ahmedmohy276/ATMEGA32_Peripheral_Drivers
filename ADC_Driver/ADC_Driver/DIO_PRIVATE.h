/*
 * DIO_REG.h
 *
 * Created: 9/14/2021 2:28:42 AM
 *  Author: ahmed
 */ 


#ifndef DIO_REG_H_
#define DIO_REG_H_

#define DDRA_REG                           (*(volatile u8*)(0X3A))
#define PORTA_REG						   (*(volatile u8*)(0X3B))
#define PINA_REG			  		       (*(volatile u8*)(0X39))

#define DDRB_REG                           (*(volatile u8*)(0X37))
#define PORTB_REG						   (*(volatile u8*)(0X38))
#define PINB_REG			  		       (*(volatile u8*)(0X36))

#define DDRC_REG                           (*(volatile u8*)(0X34))
#define PORTC_REG						   (*(volatile u8*)(0X35))
#define PINC_REG			  		       (*(volatile u8*)(0X33))

#define DDRD_REG                           (*(volatile u8*)(0X31))
#define PORTD_REG						   (*(volatile u8*)(0X32))
#define PIND_REG			  		       (*(volatile u8*)(0X30))




#endif /* DIO_REG_H_ */