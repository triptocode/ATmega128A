/*
 * FND.h
 *
 * Created: 2023-08-18 오전 9:33:06
 *  Author: user
 */ 





#ifndef FND_H_
#define FND_H_
#include <avr/io.h> // 이게 있어야 DDR 어쩌고 하는것도 사용가능


// 디지트 자리 설정  - 7segments 4자리 datasheet 참고하면   12 , 9 , 8 , 6  네자리의미
#define FND_DIGIT_1 0
#define FND_DIGIT_2 1
#define FND_DIGIT_3 2
#define FND_DIGIT_4 3

// 함수설정 -  7segments 4자리 datasheet 참고하면  위의 12자리 8비트중에 pb빼고 7자리
#define FND_DIGIT_DDR DDRG       // LED 숫자4자리를 PORTG = PG 에 핀 4개 사용?
#define FND_DIGIT_PORT DDRG
#define FND_DATA_DDR DDRC       // LED숫자 하나당 PORTC =PC 사용?
#define FND_DATA_PORT PORTC

// 함수정의
void FND_setFndDisplayData(uint16_t data);
uint16_t FND_getFndDisplayData(); 
void FND_selectDigit(uint8_t digit)
void fnd_showNumber(uint8_t fndNumber)
void FND_off()
void FND_ISR_Display()




#endif /* FND_H_ */