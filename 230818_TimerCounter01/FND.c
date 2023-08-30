/*
 * FND.c
 *
 * Created: 2023-08-18 오전 9:33:18
 *  Author: user
 */ 


#include "FND.h"

uint16_t fndDisplayData = 0; // 7 segments에 표시할 데이터 변수
void FND_Init() // 초기화 함수
{
	TCCR0 |= (1<<CS02) | (1<<CS01) | (1<<CS00); // 64분주 1/64 PRESCAL  (데이터시트 14. ~~)
	TIMSK |= (1<<TOIE0); //데이터시트 14.11.5 뒤에서 맨첫번째 비트
	TCNT0=6; // 1ms 만들기위해
	FND_DIGIT_DDR |= (1<<FND_DIGIT_1) | (1<<FND_DIGIT_2) | (1<<FND_DIGIT_3) | (1<<FND_DIGIT_4);
	FND_DATA_DDR = 0xff;
}

void FND_setFndDisplayData(uint16_t data)
{
	if(data >= 10000) // segments에 9999까지 표기 
	{
		data = 9999;
		
	}
	fndDisplayData = data;
}

uint16_t FND_getFndDisplayData()
{
	return fndDisplayData; //  변수에 저장된 데이터 반환
}

void FND_selectDigit(uint8_t digit)
{
	FND_DIGIT_PORT | = 0xf0;
	FND_DIGIT_PORT =~(1<<digit);
}

void fnd_showNumber(uint8_t fndNumber)
{
	uint8_t fndFont[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 
							0x7d, 0x27, 0x7f, 0x67};
// 	0011 1111 숫자0 , 0000 0110 숫자1,  0101 1011,  0100 1111		
	FND_DATA_PORT =fndFont[fndNumber]
}

void FND_off()
{
	FND_DIGIT_PORT |= 0xff;
}

void FND_ISR_Display()
{
	static uint8_t fndDigitPosition = 0;
	uint16_t displayData = FND_getFndDisplayData();

	fndDigitPosition = (fndDigitPosition+1)%4; // 디지트가 네자리라 4로 나눔
	FND_off();
	switch(fndDigitPosition) // fndDigitPosition=0초기값부터 시작해서, 포지션값이 1,2,3으로 변할때마다 해당 case 로직 실행~
	{
		case 0:
		fnd_showNumber(displayData %10);
		FND_selectDigit(FND_DIGIT_4);
		break;

		case 1:
		fnd_showNumber(displayData /10%10);
		FND_selectDigit(FND_DIGIT_3);
		break;

		case 2:
		fnd_showNumber(displayData / 100%10);
		FND_selectDigit(FND_DIGIT_2);
		break;

		case 3:
		fnd_showNumber(displayData /1000%10);
		FND_selectDigit(FND_DIGIT_1);
		break;
	}
}