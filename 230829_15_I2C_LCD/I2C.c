/*
 * I2C.c
 *
 * Created: 2023-08-29 오후 3:37:30
 *  Author: user
 */ 
#include "I2C.h"

void I2C_Init()
{
	I2C_DDR |= (1<<I2C_SCL) | (1<< I2C_SDA); // 출력설정	
	TWBR = 72; // 100KHz
	// TWBR = 32; // 200KHz
	// TWBR = 12; // 400KHz
}

void I2C_Start()
{
	TWCR = (1<<TWINT) | (1<<TWSTA) |(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));  // 하드웨어적으로 TWINT 시점결정
}

void I2C_Stop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) |(1<<TWSTO); // stop 비트 설정 
}


void I2C_TxData(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT))); // 전송 완료 대기 
}

void I2C_TxByte(uint8_t devAddrRw, uint8_t data)
{
	I2C_Start();
	I2C_TxData(devAddrRw);
	I2C_TxData(data);
	I2C_Stop();
}
