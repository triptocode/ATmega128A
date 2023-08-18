/*
 * LED_Shift.c
 *
 * Created: 2023-08-14 오후 2:34:22
 *  Author: user
 */
#include "LED_Shift.h"

#define LED_DDR		DDRD
#define LED_PORT	PORTD

void GPIO_Output(uint8_t data){
	LED_PORT = data;
}
void ledInit(){
	LED_DDR = 0xff;
}
void ledLeftShift(uint8_t *data){
	*data = (*data>>7)|(*data<<1);	// LED 데이터를 좌측으로 1 비트 이동
	GPIO_Output(*data);
}
void ledRightShift(uint8_t *data){
	*data = (*data<<7)|(*data>>1);	// LED 데이터를 우측으로 1 비트 이동
	GPIO_Output(*data);
}