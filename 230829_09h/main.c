/*
 * 230829_09h.c
 *
 * Created: 2023-08-29 오전 9:22:55
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0x10; // PB4출력
	TCCR0 = 0x6C; // Fast PWM, 비반전모드, 분주비 64
	// OCR0 = 64; 
	// OCR0 = 128; 
	
    while (1) 
    {
		for(int i=0; i<=256; i++)
		{
			
			 OCR0 = i;
			_delay_ms(10);
		}
    }
}

