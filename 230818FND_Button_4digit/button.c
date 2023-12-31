﻿/*
 * button.c
 *
 * Created: 2023-08-18 오전 11:34:47
 *  Author: user
 */ 
#include "button.h"
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void Button_init( // 버튼초기화 메서드 
 // < 파라미터에 일반변수가 아닌 포인터변수 3개와 일반변수1개로 만든 이유 >
 // : 일반변수는 사본을 별개로 만들어 원본을 수정못하는데, 포인터변수는 원본멤버 수정가능
	Button *button, 
	volatile uint8_t *ddr, 
	volatile uint8_t *pin,
	uint8_t pinNum )
	 
	{	button->ddr=ddr;
		button->pin=pin;
		button->btnPin=pinNum;
		button->prevState=RELEASED; //초기화 상태
		*button->ddr&=~(1<<button->btnPin); //버튼 핀 입력 설정
	}

uint8_t BUTTON_fetState(Button *button){
	uint8_t curState=*button->pin&(1<<button->btnPin); //버튼 상태 읽어오기
	if((curState==PUSHED)&&(button->prevState==RELEASED)){  // enum{PUSHED,RELEASED}; // 0 1
		_delay_ms(50); //디바운스 코드
		button->prevState=PUSHED; // 버튼을 누른상태로 변환
		return ACT_PUSH; //  enum 1
	}
	
	else if((curState !=PUSHED)&&(button->prevState==PUSHED)) //누른 상태에서 때면
	{	_delay_ms(50);
		button->prevState=RELEASED; // enum 1                // enum{PUSHED,RELEASED}; 0 1
		return ACT_RELEASED; // enum 2 버튼이 떨어졌음을 반환  // enum{NO_ACT, ACT_PUSH, ACT_RELEASED}; //0 1 2
	}
	return NO_ACT; // enum 0 아무것도 안했을때
}