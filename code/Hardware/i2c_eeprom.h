#ifndef __I2C_HAL_H
#define __I2C_HAL_H

#include "stm32f10x.h"                  // Device header

void I2CStart(void);
void I2CStop(void);
unsigned char I2CWaitAck(void);
void I2CSendAck(void);
void I2CSendNotAck(void);
void I2CSendByte(unsigned char cSendByte);
unsigned char I2CReceiveByte(void);
void I2CInit(void);
unsigned char eeprom_read(unsigned char addr);
void eeprom_white(unsigned char addr,unsigned char dat);
#endif
