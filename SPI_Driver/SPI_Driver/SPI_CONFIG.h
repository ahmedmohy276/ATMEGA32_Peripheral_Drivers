/*
 * SPI_CONFIG.h
 *
 * Created: 10/9/2021 12:16:49 AM
 *  Author: ahmed
 */ 


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#define DATA_SIZE                                 5

u8 SPI_DATA;
u8 received_Data[DATA_SIZE];

#define INT_ENABLE                                 0
#define INT_DISABLE                                1
#define LSB_ORDER                                  2
#define MSB_ORDER                                  3
#define SLAVE_MODE                                 4
#define MASTER_MODE                                5
#define RISING_FALLING                             6
#define FALLING_RISING                             7
#define SAMPLE_SETUP                               8
#define SETUP_SAMPLE                               9
#define FOSC_4                                     10
#define FOSC_16                                    11
#define FOSC_64                                    12
#define FOSC_128                                   13
#define DOUBLE_SPEED_ON                            14
#define DOUBLE_SPEED_OFF                           15
#define MASTER                                     16
#define SLAVE                                      17

#define SPI_PORT								   portB
#define SS_PIN									   4
#define MOSI_PIN								   5
#define MISO_PIN					               6
#define SCK_PIN									   7

#define NORMAL                                     0
#define ASYNCH_char		           				   1
#define RECEIVE_ASYNCH_arr					       2
#define TRANSMITT_ASYNCH_arr					   4


#define END_FLAG                                  '\0'

#endif /* SPI_CONFIG_H_ */