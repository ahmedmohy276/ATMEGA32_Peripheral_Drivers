/*
 * I2C_REGISTERS.h
 *
 * Created: 10/31/2021 1:52:45 PM
 *  Author: ahmed
 */ 


#ifndef I2C_REGISTERS_H_
#define I2C_REGISTERS_H_

#define TWDR_REG								(*((volatile u8*)(0X23)))

#define TWAR_REG								(*((volatile u8*)(0X22)))

#define TWSR_REG								(*((volatile u8*)(0X21)))

#define TWBR_REG								(*((volatile u8*)(0X20)))

#define TWCR_REG								(*((volatile u8*)(0X56)))

#define SREG_REG								(*((volatile u8*)(0X5F)))



#endif /* I2C_REGISTERS_H_ */