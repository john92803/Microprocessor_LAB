#include <reg51.h>
#define KBINP P2

unsigned char seg7[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};
void delay1ms(int count);
int kbscan();
void main(){
	int x=0;
	int y=0;
	int z=0;
	int kbin;
	P0=0x00;
	while(1){
		kbin=0xff;
		kbin = kbscan();
		if(kbin!=0xff){
			if(kbin <10){
				x = kbin;
				P0 = seg7[kbin];
			}else{
				switch(kbin){
					case 10:
						if(z>=0 && z<16){
						P0 = seg7[z];
						x=0;
						y=0;
						z=0;
						}else{
							P0 = 0xC9;
							x=0;
						y=0;
						z=0;
						}
						break;
					case 11:
						x=0;
						y=0;
						z=0;
						P0=0x00;
						break;
					case 12:
						P0=0x00;
						kbin=0xff;
					while(1){
						kbin = kbscan();
						if(kbin!=0xff){
							P0 = seg7[kbin];
							y = kbin;
							z=x+y;
							break;
						}
					}
						break;
					case 13:
						P0=0x00;
						kbin=0xff;
				while(1){
						kbin = kbscan();
						if(kbin!=0xff){
							P0 = seg7[kbin];
							y = kbin;
							z=x-y;
							break;
						}
					}
						break;
					case 14:
						P0=0x00;
						kbin=0xff;
				while(1){
						kbin = kbscan();
						if(kbin!=0xff){
							P0 = seg7[kbin];
							y = kbin;
							z=x*y;
							break;
						}
					}
						break;
					case 15:
						P0=0x00;
						kbin=0xff;
					while(1){
						kbin = kbscan();
						if(kbin!=0xff){
							P0 = seg7[kbin];
							y = kbin;
							z=x/y;
							break;
						}
					}
						break;
				}
			}
			
		}
		
		
	}
}

int kbscan(){
	unsigned char kbp;
	unsigned scanln[]={0xfe, 0xfd, 0xfb, 0xf7};
	unsigned row, col, kbtemp;
	kbp=0xff;
	for(row = 0; row<4; row++){
		KBINP=scanln[row];
		kbtemp=KBINP&0xf0;
		if(kbtemp!=0xf0){
			delay1ms(20);
			for(col=0; col<4; col++){
				if(kbtemp==((scanln[col]&0x0f)*16)){
					kbp=row*4+col;
					while((KBINP&0xf0)!=0xf0);
				}
			}
		}
	}
	return kbp;
}
void delay1ms(int count){
	int i, j;
	for(i = 0; i<count; i++)
		for(j = 0; j<1940; j++);	
}