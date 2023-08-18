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
	////sw 1�� LED 1�� ����
	//LED_DDR = 0xff;
	//SWITCH_DDR = 0x00;
    //
    //while (1) 
    //{
		//LED_PORT = 0x00;
		//
		//while(~SWITCH_PIN&0x01);		// SW ��ȣ ������ ���
		//ms_delay(100);			// ä�͸� ����
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
// LED ��̿� ����ġ ,(������ ����)
#define	F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
	DDRD = 0xff;
	DDRB = 0x00;
	
	uint8_t ledData = 0x01;
	uint8_t buttondata;			// ��ư �Է� �� ��
	int flag = 0;
	PORTD = 0x00;				// LOW ���·� ����
	
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