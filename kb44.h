#ifndef _KB44_H_
#define _KB44_H_
#include <Reg51.h>
#define KBINP P2
void delay1ms(int count);
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
		for(j = 0; j<1000; j++);	
}
#endif