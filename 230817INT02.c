/*
 * INT02.c
 *
 * Created: 2023-08-17 오후 2:10:36
 * Author : user
 */ 

// 128p 라이징엣지 , 풀업 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


uint8_t ledshift = 0xfe;

// 인터럽트 
ISR(INT4_vect)
{
	ledshift = ledshift <<1; // 기존LED상태에서 한칸씩 좌측 이동
	ledshift =ledshift | 0x01; // 현재 LED상태에서 오른쪽에 1 삽입
	if(ledshift ==0xFF)
	{
		ledshift = 0xfe;
	}
	PORTD = ledshift;

}

int main(void)
{
	PORTD = ledshift;
	EICRB |= (1<<ISC41) | (1<<ISC40);
	EIMSK |= (1<<INT4);
	DDRD =0xFF;
	DDRE &=~(1<<DDRE4);
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

