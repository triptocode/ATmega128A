/*
 * 230829_11h_UART.c
 *
 * Created: 2023-08-29 오전 11:56:28
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void UART0_init();
void UART0_transmit(char data);
unsigned UART0_receive(void);

void UART0_init()
{
	UBRR0H = 0x00; 
	UBRR0L = 207; // 9600bps 설정
	
	UCSR0A |= (1<<U2X0); // 2배속모드/ 데이터 시트 좌에 상단 핀2개있는 부분 (=1A가됨) 쓸거니까 // UCSR1A 쓰면 2배속? 
	// 비동기, 8비트 데이터, 패리티없음 , 1비트 정지모드
	// UCSR0C = 0x06; // 초기값 써줘도 되고 안써도되고
	
	UCSR0B |= (1<<RXEN0); // 수신 가능
	UCSR0B |= (1<<TXEN0); // 송신 가능
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

int main(void)
{
	UART0_init(); //0번 UART --> Initialize
	
    while (1) 
    { UART0_transmit(UART0_receive()); // 받았으면 되돌리는거 ! 
    }
}

