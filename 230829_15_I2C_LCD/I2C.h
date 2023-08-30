﻿/*
 * I2C.h
 *
 * Created: 2023-08-29 오후 3:37:44
 *  Author: user
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

#define I2C_DDR DDRD
#define	I2C_SCL PORTD0
#define	I2C_SDA PORTD1

void I2C_Init();
void I2C_Start();
void I2C_Stop();
void I2C_TxData(uint8_t data);
void I2C_TxByte(uint8_t devAddrRw, uint8_t data);


#endif /* I2C_H_ */