/*
 * I2C_CONFIG.h
 *
 * Created: 10/31/2021 1:53:03 PM
 *  Author: ahmed
 */ 


#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_


#define SCL_FREQUENCY                                   100000
#define FOSC                                            8000000


#define WRITEMODE                                       0X00
#define READMODE									    0X01

#define PRESCALER_1									    0
#define PRESCALER_4									    1
#define PRESCALER_16									2
#define PRESCALER_64									3


#define ENABLE_INT									    0
#define DISABLE_INT									    1



#define START_COND_CODE                                 0X08
#define REPEATED_START_COND_CODE                        0X10
#define SLA_WR_ACK_CODE                                 0X18
#define SLA_WR_NACK_CODE                                0X20
#define SLA_RE_ACK_CODE                                 0X40
#define SLA_RE_NACK_CODE                                0X48
#define DATA_WR_ACK_CODE                                0X28
#define DATA_WR_NACK_CODE                               0X30
#define DATA_RE_ACK_CODE                                0X50
#define DATA_RE_NACK_CODE                               0X58





#endif /* I2C_CONFIG_H_ */