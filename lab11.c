#include <reg51.h>
#include <kb44.h>
#include<intrins.h>
#define RR(x) _cror_ (x,1);
#define RL(x) _crol_ (x,1);
unsigned char seg7[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};
int state[] = {1, 1, 3};
char index = 0;
char speed[] = {10, 50, 100};
char speedindex = 0;
void delay(int count);
void sw1();void sw4();void sw8();
void int1(); void int2();
void main(){
	int i;
	TCON = 5;
	IE=0X85;
	while(1) {
		index = 0;
		P1 = seg7[state[index]];
		for(i = 0; i < state[index]; i++) 
			sw1();
		index = 1;
		P1 = seg7[state[index]];
		for(i = 0; i < state[index]; i++) 
			sw4();
		index = 2;
		P1 = seg7[state[index]];
		for(i = 0; i < state[index]; i++) 
			sw8();
	}
}

void sw1(){
	int i;
	P0 = 0xFE;
	delay(speed[speedindex]);
	for(i=0; i<7; i++){
		P0 = RL(P0);
		delay(speed[speedindex]);
	}
	P0 = 0x7F;
	delay(speed[speedindex]);
	for(i=0; i<7; i++){
		P0 = RR(P0);
		delay(speed[speedindex]);
	}
	
}
void sw4(){	
	int i, j;
	char table1[] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
	char table2[] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};
	for(i=0; i<8; i++){
		P0 = table1[i];
		delay(speed[speedindex]);
	}
	for(j=0; j<8; j++){
		P0 = ~table2[j];
		delay(speed[speedindex]);
	}
	P0 = 0x00;
	for(i=0; i<8; i++){
		P0 = table2[i];
		delay(speed[speedindex]);
	}
	for(j=0; j<8; j++){
		P0 = ~table1[j];
		delay(speed[speedindex]);
	}
	
}
void sw8(){
	P0 = ~0xFF;
	delay(speed[speedindex]);
	P0 = ~0x00;
	delay(speed[speedindex]);
}
void int1() interrupt 0 {
	int in;
	P1 = seg7[state[index]];
	while(1) {
		in = kbscan();
		if(in != 0xff) {
				state[index] = in;
				P1 = seg7[in];
				break;
		}
	}
}

void int2() interrupt 2 {
	if(speedindex == 3) {
		speedindex = 0;
	}else {
		speedindex++;
	}
}
void delay(int count){
	int i, j;
	for(i = 0; i<count; i++)
		for(j = 0; j<1940; j++);	
}