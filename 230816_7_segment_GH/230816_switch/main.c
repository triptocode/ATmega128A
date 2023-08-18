/*
#define	F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LED_DDR			DDRD
#define SWITCH_DDR		DDRB
#define LED_PORT		PORTD
#define SWITCH_PIN		PINB

#define HIGH		1
#define LOW			0

void ms_delay(int n){
	for(;n>0;n--){
		_delay_ms(1);
	}
}

int main(void)
{
	////sw 1개 LED 1개 구현
	//LED_DDR = 0xff;
	//SWITCH_DDR = 0x00;
    //
    //while (1) 
    //{
		//LED_PORT = 0x00;
		//
		//while(~SWITCH_PIN&0x01);		// SW 신호 들어오길 대기
		//ms_delay(100);			// 채터링 방지
				//
		//LED_PORT = 0x01;
		//
		//while(!(~SWITCH_PIN&0x01));
		//ms_delay(100);
		//
		//LED_PORT = 0x00;
    //}
}
*/
// LED 어레이와 스위치 ,(교수님 버전)
#define	F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
	DDRD = 0xff;
	DDRB = 0x00;
	
	uint8_t ledData = 0x01;
	uint8_t buttondata;			// 버튼 입력 시 값
	int flag = 0;
	PORTD = 0x00;				// LOW 상태로 시작
	
	while (1)
	{		
		buttondata = PINB;
		if((buttondata&(1<<0)) == 0)
		{
			PORTD = ledData;
			ledData = (ledData>>7)|(ledData<<1);
			_delay_ms(100);
		}
		
		if((buttondata&(1<<1)) == 0)
		{
			PORTD = ledData;
			ledData = (ledData>>1)|(ledData<<7);
			_delay_ms(100);
		}
		
		if((buttondata&(1<<2)) == 0)
		{
			flag = 1;
		}
		
		if ((buttondata & (1<<3))==0)
		{
			PORTD = 0x00;
		}		
		if(flag == 1)
		{
			PORTD = 0xff;
			_delay_ms(200);
			PORTD = 0x00;
			_delay_ms(200);
			if((buttondata&(1<<3)) == 0)
			{
				flag = 0;
			}
		}
		
	}
}