/*
 * 230818_TimerCounter01.c
 *
 * Created: 2023-08-18 오전 9:29:31
 * Author : user
 */ 


// 4 핀으로 입력받고 // 7핀으로 출력하는중 // vext랑 gnd는 사용안함

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "FND.h"


uint8_t counter =0;
int cnt = 0;

ISR(TIMER0_OVF_vect)
{
	cnt++;
	if(cnt == 100) // 1ms 간격을 생성 
	{
		//함수호출;
		FND_setFndDisplayData(counter++)
		cnt=0;
	}
}


int main(void)
{
	// 타이머 카운트 세팅
	void FND_Init();
	sei();
    
	while (1) 
    {
		// 디스플레이 함수
		// .c 파일에 있는 FND_ISR_Display()함수를 호출해서 4DIGIT 숫자네자리를 조건에따라 한자리씩 밀어서 로직을 반영
		FND_ISR_Display();		
    }
}

