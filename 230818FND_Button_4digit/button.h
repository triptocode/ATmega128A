/*
 * button.h
 *
 * Created: 2023-08-18 오전 11:34:32
 *  Author: user
 */ 
#ifndef BUTTON_H_
#define BUTTON_H_
#define F_CPU 16000000UL
#include <avr/io.h>

//#define LED_DDRD		DDRD
//#define LED_PORT		PORTD
//#define ButtonSub		DDRB
//#define BUTTON_ON		0
//#define BUTTON_OFF		1
//#define BUTTON_TOGGLE	2
//#define BUTTON_onOff	3

#define BUTTON_DDR		DDRA
#define BUTTON_PIN		PINA

enum{PUSHED, RELEASED};   //0 1
enum{NO_ACT, ACT_PUSH, ACT_RELEASED}; //0 1 2

typedef struct _button{	
	volatile uint8_t *ddr;
	volatile uint8_t *pin;
	uint8_t btnPin;
	uint8_t prevState;
}Button;

void Button_init(
	Button *button, 
	volatile uint8_t *ddr, 
	volatile uint8_t *pin, 
	uint8_t pinNum);
	
uint8_t BUTTON_fetState(Button *button);
#endif /* BUTTON_H_ */