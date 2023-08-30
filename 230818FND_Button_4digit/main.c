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

enum{STOP,RUN,RESET}; // 0, 1, 2   // enum 의 초기값이 없으면 0부터~
ISR(TIMER0_OVF_vect) { FND_ISR_Display(); TCNT0=6; }

int main(void)
{	FND_Init();
	TCCR0|=(1<<CS02)|(0<<CS01)|(0<<CS00);  //64분주   1/64 prescaler
	TIMSK|=(1<<TOIE0);  //타이머 카운트 오버플로우 enable
	TCNT0=6; //1ms만들기 위해
	sei();
	uint16_t counter=0;
	uint8_t counterState=STOP; // counterState = 0 
	Button btnRunStop;
	Button btnReset;
	// Button_init(Button *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum)
	Button_init(&btnRunStop, &BUTTON_DDR, &BUTTON_PIN, 0); 
	 // Button_init(Button &btnReset, volatile uint8_t &DDRA, volatile uint8_t &PINA, uint8_t 1)
	Button_init(&btnReset, &BUTTON_DDR, &BUTTON_PIN, 1);
	 while (1)
    {	switch(counterState) //	★ 1. 버튼 상황에 따른 로직의 case STOP, case RUN 
		{	case STOP: //  case STOP 숫자멈춰있는상태 --> RUN(같은스위치 PUSH할때) 또는 RESET(옆에스위치 PUSH할때)
				if(BUTTON_fetState(&btnRunStop)==ACT_PUSH) { counterState=RUN; }
				else if(BUTTON_fetState(&btnReset)==ACT_PUSH) { counterState=RESET; }
			break; 
			case RUN: //case RUN 숫자증가하는 변화상태--> STOP(같은스위치 PUSH할때) 또는 RESET(옆에스위치 PUSH할때)
				if(BUTTON_fetState(&btnRunStop)==ACT_PUSH) { counterState=STOP;}
				else if(BUTTON_fetState(&btnReset)==ACT_PUSH) { counterState=RESET; }		
		}		
		switch(counterState) // ★ 2, FND 숫자디스플레이 상황에 따른 로직 case STOP,  case RUN , case RESET
		{   case STOP: FND_setFndDisplayData(counter); // 숫자화면 멈춤
			break; 
			
			case RUN: FND_setFndDisplayData(counter++);  _delay_ms(100); // 숫자화면 증가중, 대기시간 100ms
			break;
			
			case RESET:  counter=0; FND_setFndDisplayData(counter); counterState=STOP; // 숫자화면 0 으로 리셋, STOP상태로 리셋
			break;	
		}
    } // while end
} // main end 
 
