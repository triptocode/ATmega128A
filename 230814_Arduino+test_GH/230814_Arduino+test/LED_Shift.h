#ifndef LED_SHIFT_H_
#define LED_SHIFT_H_
// 다 따로 분리할 것.
// 헤더 함수 = 많이 추가를 해도 메모리에 영향 X
#define F_CPU 16000000UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

// 하드웨어 관련 정의
#define LED_DDR		DDRD
#define LED_PORT	PORTD

// 함수 정의
void GPIO_Output(uint8_t data);
void ledInit();
void ledLeftShift(uint8_t *data);
void ledRightShift(uint8_t *data);

#endif	