/*
 * FND_Button.c
 *
 * Created: 2023-08-18 오전 11:46:58
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "button.h"
#include "interrupt.h"
#include <avr/interrupt.h>
#include <util/delay.h>


enum{STOP,RUN,RESET};
	
ISR(TIMER0_OVF_vect)
{
	FND_ISR_Display();
	TCNT0=6;
}


int main(void)
{
	
	FND_Init();
	TCCR0|=(1<<CS02)|(0<<CS01)|(0<<CS00);  //64분주   1/64 prescaler
	TIMSK|=(1<<TOIE0);  //타이머 카운트 오버플로우 enable
	TCNT0=6; //1ms만들기 위해

	sei();
	
	uint16_t counter=0;
	uint8_t counterState=STOP;
	Button btnRunStop;
	Button btnReset;
	
	Button_init(&btnRunStop,&BUTTON_DDR,&BUTTON_PIN,0);
	Button_init(&btnReset,&BUTTON_DDR,&BUTTON_PIN,1);
	
	
    /* Replace with your application code */
    while (1) 
    {
		switch(counterState)
		{
			case STOP:
			if(BUTTON_fetState(&btnRunStop)==ACT_PUSH)
			{
				counterState=RUN;

			}
			else if(BUTTON_fetState(&btnReset)==ACT_PUSH)
			{

				counterState=RESET;
	
			}
			break; 
			
			case RUN:
			if(BUTTON_fetState(&btnRunStop)==ACT_PUSH)
			{
				counterState=STOP;
	
			}
	
			
		}
		
		switch(counterState)
		{
			case STOP:
			FND_setFndDisplayData(counter);
			break; 
			
			case RUN:
			FND_setFndDisplayData(counter++);
			
			_delay_ms(100);
			break;
			
			case RESET:
			counter=0;
			FND_setFndDisplayData(counter);
			counterState=STOP;
			break;
		}
    }
}

