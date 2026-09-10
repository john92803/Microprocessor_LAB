#include<reg51.h>
sbit sw1 = P2^7;
sbit sw2 = P2^6;
sbit sw3 = P2^5;
sbit sw4 = P2^4;
sbit sw5 = P2^3;
sbit sw6 = P2^2;
sbit sw7 = P2^1;
sbit sw8 = P2^0;
int upperbound, lowerbound;
int display = 0;
int display1 = 0;
int display2 = 0;
void delay10ms(int count);
void fn1();void fn2();void fn3();void fn4();
void count1();void count2();
char seg7[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};
void main(){
		P0 = seg7[0];
		while(1){
			if(sw1 == 1 && sw2 == 1) do{fn1();}while(sw1 == 1 && sw2 == 1);
			else if(sw1 == 1 && sw2 == 0) do{fn2();}while(sw1 == 1 && sw2 == 0);
			else if(sw1 == 0 && sw2 == 1) do{fn3();}while(sw1 == 0 && sw2 == 1);
			else if(sw1 == 0 && sw2 == 0) do{fn4();}while(sw1 == 0 && sw2 == 0);
		}
}
void fn1(){
	count1();
	upperbound = display;
	P0 = seg7[upperbound];
}
void fn2(){
	count2();
	lowerbound = display;
	P0 = seg7[lowerbound];
}
void fn3(){
	int i;
	for(i = 0; i<=upperbound; i++){
		P0 = seg7[i];
		delay10ms(100);
		if(i == upperbound+1 && (sw1 == 0 && sw2 == 1)) i = 0;
	}
}
void fn4(){
	int i;
	for(i = lowerbound; i>=0; i--){
		P0 = seg7[i];
		delay10ms(100);
		if(i == 0 && (sw1 == 0 && sw2 == 0)) i = lowerbound+1;
	}
}
void count1(){
	display = 0;
	if(~sw5)display+=8;
	if(~sw6)display+=4;
	if(~sw7)display+=2;
	if(~sw8)display+=1;
}
void count2(){
	display = 0;
	display1 = 0;
	display2 = 0;
	if(~sw3)display1+=4;
	if(~sw4)display1+=2;
	if(~sw5)display1+=1;
	if(~sw6)display2+=4;
	if(~sw7)display2+=2;
	if(~sw8)display2+=1;
	display = display1 + display2; 
}
void delay10ms(int count){
	int i,j;
	for(i=0;i<count;i++){
		for(j=0;j<1940;j++);
	}
}