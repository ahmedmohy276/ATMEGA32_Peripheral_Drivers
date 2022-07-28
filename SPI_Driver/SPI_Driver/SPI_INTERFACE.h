/*
 * SPI_INTERFACE.h
 *
 * Created: 10/9/2021 12:16:30 AM
 *  Author: ahmed
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "STD_TYPES.h"

void SPI_VoidSPIInitialization(u8 Mode,u8 INT_status,u8 data_order,u8 clk_polarity,u8 clk_phase,u8 clk_Rate,u8 double_speed_status);

void SPI_VoidMasterInit(void);

void SPI_VoidSlaveInit(void);

void SPI_VoidInterruptEnable(u8 status);

void SPI_VoidSetDataOrder(u8 data_order);

void SPI_VoidSetClockPolarity(u8 clk_polarity);

void SPI_VoidSetClockPhase(u8 clk_phase);

void SPI_VoidSetClockRate(u8 clk_Rate);

void SPI_VoidSetDoubleSpeed(u8 status);


void SPI_VoidSeCallBackFunc(void (*ptrToFunc) (void));

u8 SPI_U8_SynchSendData(u8 data);

void SPI_VoidASynchSendData(u8 data);

u8* SPI_U8_SynchSendString(u8* data);

void SPI_VoidASynchSendString(u8 *data);

u8 SPI_U8_SynchReceiveData(u8 data);

void SPI_VoidASynchReceiveData(u8 data,u8* data_received);

u8* SPI_U8_SynchReceiveString(u8 *data);

void SPI_VoidASynchReceiveString(u8 *data,u8* data_received);

#endif /* SPI_INTERFACE_H_ */