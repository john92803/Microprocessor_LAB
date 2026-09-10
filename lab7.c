#include<reg52.h>
#include<intrins.h>
#define RR(x) _cror_ (x,1);
#define RL(x) _crol_ (x,1);
void delay(int count);
void sw1();void sw4();void sw8();
void main(){
	P0 = ~0x00;
	while(1){
		switch(~P2){
			case 0x01:
				P0 = 0xFF;
				do{
					sw1();
				}while(~P2 == 0x01);
				break;
			case 0x08:
				P0 = 0xFF;
				do{
					sw4();
				}while(~P2 == 0x08);
				break;
			case 0x80:
				P0 = 0xFF;
				do{
					sw8();
				}while(~P2 == 0x80);
				break;
			case 0x89:
				P0 = 0xFF;
				do{
					sw1();
					sw4();
					sw8();
					sw8();
					sw8();
				}while(~P2 == 0x89);
				break;
			default:
				P0 = ~0x00;
				break;
		}
	}
}
void sw1(){
	int i;
	P0 = 0xFE;
	delay(10);
	for(i=0; i<7; i++){
		P0 = RL(P0);
		delay(10);
	}
	P0 = 0x7F;
	delay(10);
	for(i=0; i<7; i++){
		P0 = RR(P0);
		delay(10);
	}
	
}
void sw4(){	
	int i, j;
	char table1[] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
	char table2[] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};
	for(i=0; i<8; i++){
		P0 = table1[i];
		delay(10);
	}
	for(j=0; j<8; j++){
		P0 = ~table2[j];
		delay(10);
	}
	P0 = 0x00;
	for(i=0; i<8; i++){
		P0 = table2[i];
		delay(10);
	}
	for(j=0; j<8; j++){
		P0 = ~table1[j];
		delay(10);
	}
	
}
void sw8(){
	P0 = ~0xFF;
	delay(10);
	P0 = ~0x00;
	delay(10);
}
void delay(int count){
	int i, j;
	for(i = 0; i<count; i++)
		for(j = 0; j<1940; j++);
}