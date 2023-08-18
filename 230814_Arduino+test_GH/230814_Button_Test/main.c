#define F_CPU 16000000UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#define DDR_LED		DDRC	
#define PORT_LED	PORTC
#define	DDR_BUTTON	DDRD
#define	PORT_BUTTON	PORTD
#define HIGH	1
#define LOW		0

int main(void)
{
    DDR_LED = 0xff;
	PORT_LED = 0x00;
	DDR_BUTTON =0x00;
		
	//uint8_t i=0;
	
	while (1) 
    {
		if((PORT_BUTTON&0x01)==1){
			_delay_ms(1000);
			
			for (uint8_t i = 0; i<8;i++){
			PORT_LED = 0x00+i;
			_delay_ms(500);
			}
		}
		
			//_delay_ms(1000);
			//i++;
			//if(i>5){
				//i=0;
			//}	
		//}
		//
		//PORT_LED = 0x00+i;
		//_delay_ms(1000);
			
    }
	
}

