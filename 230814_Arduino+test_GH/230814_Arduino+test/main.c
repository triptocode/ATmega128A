#include "LED_Shift.h"

//int main(void)
//{
    //LED_DDR = 0xff;
	//LED_PORT = 0x00;
	//
	//while (1) 
    //{
		//
		//for (uint8_t i = 0; i<8;i++){
			//LED_PORT = 0x01<<i;
			//_delay_ms(500);				
		//}
		//for (uint8_t i = 0; i<8;i++){
			//LED_PORT = 0x80>>i;
			//_delay_ms(500);
		//}
			//
    //}
	//
//}
//
//int main(void){
	//ledInit();
	//uint8_t ledData = 0x01;
	//
	//while(1){
		//for(int i=0; i<7; i++){
			//ledLeftShift(&ledData);
			//_delay_ms(200);
		//}
		//for(int i=0; i<7; i++){
			//ledRightShift(&ledData);
			//_delay_ms(200);
		//}
	//}
//}

//int main(void){
	//ledInit();
	//LED_PORT = 0x00;
	//
	//while(1){
		//
		//for(int i=0;i<3;i++){
			//LED_PORT = (0x01<<i)|(0x80>>i);
			//_delay_ms(500);
		//}
		//for (int i = 3; i>0; i--)
		//{
			//LED_PORT = (0x01<<i)|(0x80>>i);
			//_delay_ms(500);
		//}
	//}
//}

//int main(void){
	//ledInit();
	//LED_PORT = 0x00;
	//
	//while(1){
		//
		//for(int i=0;i<8;i++){
			//LED_PORT |= (0x01<<i);
			//_delay_ms(200);
		//}
		//for (int i = 0; i<8; i++){
		//LED_PORT &= ~(0x01<<i);
		//_delay_ms(200);
		//}
	//}
//}
// 7-세그먼트
//- Common-Cathode (CC): GND를 하나로 묶은 것, 켜고 싶은 곳에 Vcc를 입력.
//- Common-Anode(CA): VCC를 하나로 묶은 것. 켜고 싶은 곳에 GND를 연결.

int seg[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 
			0x6D, 0x7D, 0x27, 0x7F, 0x6F };
	
int main(void){
	ledInit();
	while(1){
		for (int i=0; i<10; i++)
		{
			LED_PORT = ~seg[i];
			_delay_ms(500);
		}
		LED_PORT = 0x00;
		_delay_ms(3000);
	}
	
}