/*
 * interrupt.c
 *
 * Created: 2023-08-18 오전 9:32:09
 *  Author: user
 */ 
#include "interrupt.h"
uint16_t fndDisplayData=0;  //7세그먼트에 표시할 데이터 변수 

void FND_Init(){
	//TCCR0|=(1<<CS02)|(0<<CS01)|(0<<CS00);  //64분주   1/64 prescaler 
	//TIMSK|=(1<<TOIE0);  //타이머 카운트 오버플로우 enable 
	//TCNT0=6; //1ms만들기 위해 
	FND_DIGIT_DDR|=(1<<FND_DIGIT_1)|(1<<FND_DIGIT_2)|(1<<FND_DIGIT_3)|(1<<FND_DIGIT_4);	
	FND_DATA_DDR=0xFF; 
}

void FND_setFndDisplayData(uint16_t data)
{	if(data>=10000) //세그먼트에 9999까지 표기 
	{	data=9999;
		//fndDisplayData=data;	
	}
	fndDisplayData=data;
}

uint16_t FND_getFndDisplayData()
{	return fndDisplayData; //변수에 저장된 데이터 반환 	
}

void FND_selectDigit(uint8_t digit) //자릿수 선택 
{	FND_DIGIT_PORT|=0xf0;
	FND_DIGIT_PORT=~(1<<digit);	
}

void fnd_showNumber(uint8_t fndNumber)
{	uint8_t fndFont[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x67};
	FND_DATA_PORT=fndFont[fndNumber];
}

void FND_off(){	FND_DIGIT_PORT|=0xff;	}
void FND_ISR_Display()
{	static uint8_t fndDigitPosition=0;
	uint16_t displayData=FND_getFndDisplayData();
	fndDigitPosition=(fndDigitPosition+1)%4; 
	FND_off();
	
	switch (fndDigitPosition)
	{	case 0:
		fnd_showNumber(displayData%10);
		FND_selectDigit(FND_DIGIT_4);
		break; 
		
		case 1:
		fnd_showNumber(displayData/10%10);
		FND_selectDigit(FND_DIGIT_3);
		break;
		
		case 2:
		fnd_showNumber(displayData/100%10);
		FND_selectDigit(FND_DIGIT_2);
		break;
		
		case 3:
		fnd_showNumber(displayData/1000%10);
		FND_selectDigit(FND_DIGIT_1);
		break;
	}
}