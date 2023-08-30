/*
 * interrupt.h
 *
 * Created: 2023-08-18 오전 9:32:28
 *  Author: user
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/io.h>
#define FND_DIGIT_1 0
#define FND_DIGIT_2 1
#define FND_DIGIT_3 2
#define FND_DIGIT_4 3

#define FND_DIGIT_DDR DDRG	
#define FND_DIGIT_PORT PORTG
#define FND_DATA_DDR DDRC
#define FND_DATA_PORT PORTC

//함수정의 

void FND_Init();
void FND_setFndDisplayData(uint16_t data);
uint16_t FND_getFndDisplayData();
void FND_selectDigit(uint8_t digit);
void fnd_showNumber(uint8_t fndNumber);
void FND_off();
void FND_ISR_Display();





#endif /* INTERRUPT_H_ */