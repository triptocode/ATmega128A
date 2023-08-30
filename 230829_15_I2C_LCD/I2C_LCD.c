/*
 * I2C_LCD.c
 *
 * Created: 2023-08-29 오후 4:20:52
 *  Author: user
 */ 

#include "I2C_LCD.h"

void LCD_Data4bit(uint8_t data)
{
	
}

void LCD_EnablePin()
{
	
}
void LCD_WriteCommand(uint8_t commandData)
{
	
}
void LCD_WriteData(uint8_t charData)
{
	
}
void LCD_BackLightOn()
{
	
}
void LCDGotoXY(uint8_t row, uint8_t col)
{
	
}
void LCD_WriteString(char *string)
{
	
}
void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string)
{
	
}

void LCD_init()
{
	I2C_Init();
	
	_delay_ms(20);
	LCD_WriteCommand(0x03);
	_delay_ms(10);
	LCD_WriteCommand(0x03);
	_delay_ms(1);
	LCD_WriteCommand(0x03);
	
	LCD_WriteCommand(0x02);
	LCD_WriteCommand(COMMAND_4_BIT_MODE);
	LCD_WriteCommand(COMMAND_DISPLAY_OFF);
	LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
	LCD_WriteCommand(COMMAND_ENTRY_MODE);
	LCD_WriteCommand(COMMAND_DISPLAY_ON);
	LCD_BackLightOn();
	
}


