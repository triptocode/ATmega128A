/*
 * 230817InterruptApplication1.c
 *
 * Created: 2023-08-17 오전 11:38:19
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT4_vect) // 4번핀(INT4)
{
	PORTD ^=(1<<0); // 0번핀
}
ISR(INT5_vect)
{
	PORTD ^=(1<<1);  // 1번핀
}

int main(void)
{
	// 외부 인터럽트 INT4(PE4), INT5(PE5)
	
	// INT4번이 falling edge 일때 인터럽트 발생  (버튼을눌렀을때 발생?)  -> 버튼 눌릴때
	EICRB |= (1<<ISC41) | (0<<ISC40); // | (0<<ISC40);는 0이라 안써줘도 되는데 볼때 일관성 때문에 작성함 
	
	// INT5번이 rising edge 일때 인터럽트 발생  -> 버튼 놓을때
	EICRB |= (1<<ISC51) | (1<<ISC50);
	
	//INT4, INT5 쓸거라고 셋팅
	EICRB |= (1<<INT5) | (1<<INT4);  // 첫째) 비트 1을 좌측으로 5자리만큼 위치시켜 놓기. 0000 0000 -> 0010 0000, 둘째)비트1을 좌측으로 4자리만큼 위치시켜 놓기. 0000 0000 -> 0010 0000, 셋째) 합친연산은 0011 0000
	 
	DDRE &=~((1<<DDRE4) | ~(1<<DDRE5)); // 입력으로 세팅 (버튼)

	DDRD =0xff; // LED포트 
	
	sei(); // 외부 인터럽트 활성화 
     // cli() // 외부 인터럽트 비활성
	 while (1) 
    {
		
    }
}

