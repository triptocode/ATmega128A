/*
 * 230829_11h_UART_INT.c
 *
 * Created: 2023-08-29 오후 2:25:22
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "UART.h"

// 출력스트림 설정
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

char rxBuff[100] = {0,}; // 수신버퍼
	uint8_t rxFlag = 0; // 수신완료 플래그

ISR(USART0_RX_vect) // 수신인터럽트 핸들러 
{
	static uint8_t rxHead = 0; // 수신데이터 인덱스
	uint8_t rxData = UDR0;
	if(rxData =='\n' || rxData =='|r') // 개행문자나 리턴문자면  (둘째줄에 입력한 ㄴ문자 buff)
	{
		rxBuff[rxHead] = '\0'; // 수신된 문자열 마지막에 Null 추가 
		rxHead =0; // 인덱스 초기화
		rxFlag =1; // 문자열 수신 플래그 설정
	}
	else // compoartmaster에서 첫줄데이터 입력한1234 를 세번보내는게 출력됨 
	{
		rxBuff[rxHead] = rxData; // 버퍼에 수신된 데이터 추가 
		rxHead++; // 인데스 증가 
	}
}

int main(void)
{
	UART0_init();
	//uint8_t rxData; // 수신데이터
    stdout = &OUTPUT;
	sei();
	
	while (1) 
    {
		if(rxFlag ==1)
		{
			rxFlag =0;
			printf(rxBuff);
		}
    }
}

