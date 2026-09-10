#include <reg51.h>
sbit Btn = P1^0;
sbit A0 = P2^4;
sbit A1 = P2^5;
sbit A2 = P2^6;
sbit A3 = P2^7;
sbit B0 = P2^0;
sbit B1 = P2^1;
sbit B2 = P2^2;
sbit B3 = P2^3;
sbit L0 = P0^0;
sbit L1 = P0^1;
sbit L2 = P0^2;
sbit L3 = P0^3;
sbit L4 = P0^4;
sbit L5 = P0^5;
sbit L6 = P0^6;
sbit L7 = P0^7;
void delay10ms(int count);
int getNumber(bit S0, bit S1, bit S2, bit S3);
void plus(int A, int B);
void minus(int A, int B);
void and_cal();
void or_cal();
void main(){
	int status = 1;
	int A,B;
	P0 = 0xff;
	while(1){
		while(Btn == 1){
			A = getNumber(~A0,~A1,~A2,~A3);
			B = getNumber(~B0,~B1,~B2,~B3);
			switch(status){
				case 1:
					plus(A,B);
					break;
				case 2:
					minus(A,B);
					break;
				case 3:
					and_cal();
					break;
				case 4:
					or_cal();
					break;
			}
		}
		delay10ms(2);
		if(Btn == 0){
			P0 = 0xff;
			status++;
			if(status == 5)
				status = 1;
			while(Btn == 0);
			delay10ms(2);
			while(Btn == 0);
		}
	}
}

void plus(int A, int B){
	int low = (A+B) % 10;
	int high = (A+B) / 10;
	L3 = !(low >= 8);
  low = low % 8;
  L2 = !(low >= 4);
  low = low % 4;
  L1 = !(low >= 2);
  low = low % 2;
  L0 = !(low >= 1);
	
	L6 = !(high >= 4);
  high = high % 4;
  L5 = !(high >= 2);
  high = high % 2;
  L4 = !(high >= 1);
}

void minus(int A, int B){
	int low,high;
	if(A < B){
		L7 = 0;
		low = (B-A) % 10;
		high = (B-A) / 10;
		L3 = !(low >= 8);
		low = low % 8;
		L2 = !(low >= 4);
		low = low % 4;
		L1 = !(low >= 2);
		low = low % 2;
		L0 = !(low >= 1);
		
		L6 = !(high >= 4);
		high = high % 4;
		L5 = !(high >= 2);
		high = high % 2;
		L4 = !(high >= 1);
	}else{
		L7 = 1;
		low = (A-B) % 10;
		high = (A-B) / 10;
		L3 = !(low >= 8);
		low = low % 8;
		L2 = !(low >= 4);
		low = low % 4;
		L1 = !(low >= 2);
		low = low % 2;
		L0 = !(low >= 1);
		
		L6 = !(high >= 4);
		high = high % 4;
		L5 = !(high >= 2);
		high = high % 2;
		L4 = !(high >= 1);
	}
}

void and_cal(){
	L0 = ~(A0 & B0);
	L1 = ~(A1 & B1);
	L2 = ~(A2 & B2);
	L3 = ~(A3 & B3);
}

void or_cal(){
	L0 = ~(A0 | B0);
	L1 = ~(A1 | B1);
	L2 = ~(A2 | B2);
	L3 = ~(A3 | B3);
}

int getNumber(bit S0, bit S1, bit S2, bit S3){
	int r=0;
	if(~S0) r+=1;
	if(~S1) r+=2;
	if(~S2) r+=4;
	if(~S3) r+=8;
	return r;
}

void delay10ms(int count){
	int i,j;
	for(i=0;i<count;i++){
		for(j=0;j<1940;j++);
	}
}