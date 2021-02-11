#include <GAME_BALL.h>
#include "stm32f10x.h"
#include "delay.h"
#include "oled.h"
#include "usart.h"
#include "math.h"
#include <stdlib.h>

unsigned char flag = 0;
unsigned char score = 0;

unsigned char ctime[3];
extern unsigned char time;
unsigned char a[4];



//Ð¡ÇòÒÆ¶¯
unsigned char BallCtl(int roll,int pitch,unsigned char *x,unsigned char *y)
{ 
	unsigned char lx,ly,speed;
	lx = *x;
	ly = *y;
	
/////////////////////////////y///////////////////////////////////////
	
	if(roll>0){
		if(roll>15){
			*y = *y-1;
		}
		*y = *y-1;
	}
	
	
	if(roll<0){
		if(roll <= -15){
			*y = *y+1;
		}
		*y = *y+1;
	}
	
//////////////////////////////x/////////////////////////////////////
	
	if(pitch>0){
		if(pitch>15){
			*x = *x-1;
		}
		*x = *x-1;
	}
	
	if(pitch<0){
		if(pitch <= -15){
			*x = *x+1;
		}
		*x = *x+1;
	}
	
	if(*y<=2){*y = 2;}
	if(*x>127){ *x = 127;}
	if(*x<=32){ *x = 32;}
	if(*y>=62){ *y = 62;}



	delay_ms(10);
	BallMove(*x,*y,lx,ly);
	return score;
}



void BallMove(unsigned char x,unsigned char y,unsigned char lx,unsigned char ly){
	Clear_Point1(lx,ly);
	Draw_Point1(x,y);
	GeneratePoint((x-y+ly-lx+14)*12,x,y);	
	printf("\r\n x = %d,y = %d\r\n",x,y);
}

void GeneratePoint(unsigned char srand,unsigned char x1,unsigned char y1)
{
	static unsigned char x,y;
	if(abs(x1-x)<=3&& abs(y1-y)<=3){
		flag = 0;
		Clear_Point1(x,y);
		score++;
		delay_ms(1);
	}
	if(flag == 0 ){
	x = (x*23*srand+34)%94+32;
	y = (y*33*srand+111)%63;
		delay_ms(1);
	
	flag = 1;
	}
	Draw_Point1(x,y);

}


void Draw(void){
	    ctime[1] = time/2%10+'0';
		ctime[0] = time/2/10+'0';
		

		a[2] = (int)score%10+'0';
		a[1] = (int)score/10%10+'0';
		a[0] = (int)score/100+'0';
		a[3] = '\0';

		//ctime[2] = '\0';
		OLED_P6x8Str(0,5,"time");
		OLED_P6x8Str(0,6,ctime);
	

		OLED_P6x8Str(0,1,"score");
		OLED_P6x8Str(0,3,a);


		if(time ==0)
		OLED_CLS();

}


