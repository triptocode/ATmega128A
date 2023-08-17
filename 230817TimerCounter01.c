/*
 * TimerCounter01.c
 *
 * Created: 2023-08-17 오후 4:16:56
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int cnt; // 카운트 값을 저장할 변수 

ISR(TIMER0_OVF_vect) // 타이머 카운터 0번 오버플로우 인터럽트 서비스루틴
{
	cnt++; //변수값 1 증가 
	TCNT0 = 131; // 타이머카운트0번쓸거라.., // 2ms 만들기 위해 TCNT 초기값을 설정 
	
	if(cnt==500) // 500번째 발생.. 2ms*500 =1초   // 100이나 다른 숫자도 넣어보자. 
	{
		PORTD = ~PORTD; // LED 출력 반전 : 불켜져있으면 끄고, 꺼져있으면 키고! 
		cnt =0;			// cnt 값 0으로 초기화
	}
}

int main(void)
{
	DDRD = 0xff;
	PORTD = 0x00;
	
	TCCR0 = (1<<CS02) | (1<<CS01) | (0<<CS00); // 256분주
	TIMSK = (1<<TOIE0);
	
	sei();
	
    while (1) 
    {
    }
}

