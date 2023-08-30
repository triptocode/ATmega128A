/*
 * 230829_10h_Fast_PWM_16bit.c
 *
 * Created: 2023-08-29 오전 10:44:37
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0x20; // PB5, OC1A / PB5는 001010000
	TCCR1A |= (1<<COM1A1 |(1<<WGM11));//10000010 표에서 윗줄세팅
	TCCR1B |= (1<<WGM13)|(1<<WGM12)|(1<<CS11) |(1<<CS10);// 표에서 아랫줄 세팅
	TCCR1C =0; // 디폴트 0이라 안써줘도 되는데 우린 알아보기 쉽게 작성함 
	
	//OCR1A= 625;   // 25% duty
	//OCR1A= 1250;  // 50% duty
	//OCR1A= 1875;  // 75% duty

	ICR1 = 2499;  // 9시에 했던 코드에서는 TOP값이 255였는데 지금 10시 코드는 우리가 TOP 값을 2499로 설정해줌  HIGH가 25퍼센트뜸 
	
    while (1) 
    {
		for(int i=0; i<=2499; i++)
		{
			OCR1A = i;
			_delay_ms(2);
		}
		
    }
}

