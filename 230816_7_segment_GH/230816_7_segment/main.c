#define	F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LED_DDR		DDRB
#define NUM_DDR		DDRD
#define LED_PORT	PORTB
#define NUM_PORT	PORTD

static int seg_num[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F };
	
int main(void)
{
    LED_DDR = 0xff;
	NUM_DDR = 0xff;
	uint16_t num = 0;
	
    while (1) 
    {		
		//// 시간별 카운터		
		//for (int i=0; i<4; i++){
			//LED_PORT = ~(0x01<<i);
			//switch(i)	// 현재 출력할 자리에 따라 해당자리 출력
			//{
				//case 0:
				//NUM_PORT = seg_num[num%10];
				//break;
				//
				//case 1:
				//NUM_PORT = seg_num[num/10%10];
				//break;
				//
				//case 2:
				//NUM_PORT = seg_num[num/100%10];
				//break;
				//
				//case 3:
				//NUM_PORT = seg_num[num/1000];
				//break;
			//}
			//_delay_ms(5);
		//}
		//
		//num ++;
		//if (num>10000) num=0;
		
		// 자리수 별 출력 보기용
		for (int j=0; j<4;j++)
		{
			LED_PORT = ~(0x01<<j);
			for (int i=0; i<10; i++)
			{
				NUM_PORT = seg_num[i];
				_delay_ms(300);
			}
		}
    }
}

/*
// 시간별 카운터(교수님거)
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define FND_DATA_DDR    DDRD    // 데이터 포트 설정
#define FND_SELECT_DDR    DDRB    // 셀렉트(디지트) 설정
#define FND_DATA_PORT    PORTD    // 데이터 출력 설정
#define FND_SELECT_PORT    PORTB    // 셀렉트 설정

void FND_Display(uint16_t data);    // 디스플레이 함수, 4자리 표현을 위해 16비트 설정

int main(void)
{
	FND_DATA_DDR = 0xFF;        // DDRD 포트 출력 설정.
	FND_SELECT_DDR = 0xFF;        // DDRB 포트 출력 설정.
	FND_SELECT_PORT = 0x00;        // PORTB 초기값 0 설정.
	uint16_t count = 0;            // 변수 선언.
	uint32_t timeTick = 0;        // 변수 선언.
	uint32_t prevTime = 0;        // 변수 선언.

	while (1)
	{
		FND_Display(count);        // 함수 호출 count값 넘김.
		if(timeTick - prevTime > 100)    // 100ms가 지날때마다 count값 1씩 증가.
		{
			prevTime = timeTick;
			count ++;
		}
		_delay_ms(1);
		timeTick ++;
	}
}
void FND_Display(uint16_t data) {

	static uint16_t position = 0;    // 정적변수 선언.
	uint16_t fndData[10] =
	{
		0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67
	};
	switch(position)    // 현재 출력할 자리(position)에 따라 해당자리 출력.
	{
		case 0:
		// 첫번째 자리 출력위해 첫번째 핀 LOW, 2, 3, 4핀 HIGH 설정.
		FND_SELECT_PORT &= ~(1<<0);
		FND_SELECT_PORT |= (1<<1) | (1<<2) | (1<<3);
		// 입력된 데이터의 천의 자리를 구하여 FND에 출력.
		FND_DATA_PORT = fndData[data/1000];
		break;

		case 1:
		// 두번째 자리 출력위해 2핀 LOW, 1, 3, 4핀 HIGH 설정.
		FND_SELECT_PORT &= ~(1<<1);
		FND_SELECT_PORT |= (1<<0) | (1<<2) | (1<<3);
		// 입력된 데이터의 천의 자리를 구하여 FND에 출력.
		FND_DATA_PORT = fndData[data/100%10];
		break;

		case 2:
		// 세번째 자리 출력위해 3핀 LOW, 1, 2, 4핀 HIGH 설정.
		FND_SELECT_PORT &= ~(1<<2);
		FND_SELECT_PORT |= (1<<0) | (1<<1) | (1<<3);
		// 입력된 데이터의 천의 자리를 구하여 FND에 출력.
		FND_DATA_PORT = fndData[data/10%10];
		break;

		case 3:
		// 네번째 자리 출력위해 4째 핀 LOW, 1, 2, 3핀 HIGH 설정.
		FND_SELECT_PORT &= ~(1<<3);
		FND_SELECT_PORT |= (1<<0) | (1<<1) | (1<<2);
		// 입력된 데이터의 천의 자리를 구하여 FND에 출력.
		FND_DATA_PORT = fndData[data%10];
		break;
	}
	position ++;            // 다음자리 이동을 위해 포지션값 증가.
	position = position %4;    // 4자리 출력 후 다시 첫번째로 돌아가기 위해 4로 나눈 나머지 값 저장.
}

*/