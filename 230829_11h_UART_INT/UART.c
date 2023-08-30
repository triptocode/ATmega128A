/*
 * UART.c
 *
 * Created: 2023-08-29 오후 2:27:17
 *  Author: user
 */ 

#include "UART.h"

void UART0_init()
{
	UBRR0H = 0x00;
	UBRR0L = 0xCF;  // 207 이랑 같음 헥사값 !  // 9600bps 설정
	
	UCSR0A |= (1<<U2X0); // 2배속모드/ 데이터 시트 좌에 상단 핀2개있는 부분 (=1A가됨) 쓸거니까 // UCSR1A 쓰면 2배속?
	// 비동기, 8비트 데이터, 패리티없음 , 1비트 정지모드
	// UCSR0C = 0x06; // 초기값 써줘도 되고 안써도되고
	
	UCSR0B |= (1<<RXEN0); // 수신 가능
	UCSR0B |= (1<<TXEN0); // 송신 가능
	
	UCSR0B |= (1<<RXCIE0);  // 수신인터럽트 enable (수신완료 인터럽트 허용)
}

void UART0_transmit(char data) // // RXC0이나온 이유: 수신할 문제가 있으면 1 / 1&1이면 1인데 반전!을 걸었으니  0이 될때 하단 줄이 실행됨
{
	while(!(UCSR0A &(1<<UDRE0))); //  송신 가능대기, UDR이 비어있는지  .. 비어있으면 이 줄에서 돌다가... 비어있지 않으면 다음줄? 진행
	UDR0 =data; // 데이터전송
}

unsigned UART0_receive(void)
{
	while(!(UCSR0A &(1<<RXC0))); // 데이터 수신 대기
	return UDR0;
}