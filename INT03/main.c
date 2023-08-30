/*
 * INT03.c
 *
 * Created: 2023-08-17 오후 3:04:02
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t ledshift =0XFE; // 0XFE는 1111 1110
volatile uint8_t button_pressed =0; // volatile는 최적화하지마라는 의미

ISR(INT4_vect) // 핀 4번과 연결된
{	button_pressed =1; // 인터럽트가 들어오면 이부분만 바꿔줄것이다. 
}

int main(void)
{	DDRD =0xff;
	DDRE &=~(1<<DDRE4);
	PORTD =ledshift; // 0xFE;
	
	EICRB |=(1<<ISC41) | (0<<ISC40); // ISC41,ISC40은 하나의 핀인 INT4(=PE4)에 들어가는 비트값 옵션 두개자리를 말한다. 1 0 으로 들어가면 falling edge 
	EIMSK |= (1<<INT4);
	sei();
	
    while (1) 
    { if(button_pressed)
		{	_delay_ms(50);
			if(!(PINE &(1<<PINE4)))
			{	ledshift=(ledshift<<1) | 0x01;
				if(ledshift ==0xff)
				{ ledshift = 0xfe; };
				PORTD =ledshift;
			}
			button_pressed =0; // 버튼입력상태초기화/ 버튼을계속눌린상태에서도 LED이동하지않게?
		}
    }
}

