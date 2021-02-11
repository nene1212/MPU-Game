#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "oled.h"
#include "bmp.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "GAME_BALL.h"
#include "timer.h"
#include "stm32f10x_tim.h"  

/****************PIN DEFINE************************/
/**************************************************/
/**************************************************/
/*            ********OLED********                */
/*                                                */  
/*        PC14->SCL      	PC15->SDA	          */
/*                                                */  
/*          ******MPU6050/9250********            */
/*                                                */  
/*        PB10->SCL      	PB11->SDA	          */
/*                                                */
/**************************************************/
/**************************************************/



#define KEY GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)

void KEY_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}

int main()
{
	float pitch,roll,yaw; 		//ŷ����
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;	//������ԭʼ����
	short temp;					//�¶�
	unsigned char x,y,score;
	unsigned char *x1,*y1;
	
	unsigned char a[3];	
	x = 64;
	y = 32;
	x1 = &x;
	y1 = &y;
    delay_init(); //��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(500000);  //����ͨ�ų�ʼ��
    OLED_GPIO_Init();
	//MPU_Init();					//��ʼ��MPU6050
    OLED_Init();
			OLED_P8x16Str(0,3,"Loading...");

	KEY_GPIO_Init();
	while(mpu_dmp_init())
		{
			OLED_P8x16Str(0,3,"Loading...");
			delay_ms(200);
			
		}
	OLED_CLS();

	OLED_P8x16Str(0,3,"Press To Start");

	while(KEY == 1);
	OLED_CLS();
	TIM3_Int_Init(4999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 

	while(1)
	{
		while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0){		
			temp=MPU_Get_Temperature();	//�õ��¶�ֵ
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������	
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			temp = temp/10;
			
			}
		
		OLED_Set_Pos(30,0);
		OLED_WrDat(0XFF);
		OLED_Set_Pos(30,1);
		OLED_WrDat(0XFF);
		OLED_Set_Pos(30,2);
		OLED_WrDat(0XFF);
		OLED_Set_Pos(30,3);
		OLED_WrDat(0XFF);
		OLED_Set_Pos(30,4);
		OLED_WrDat(0XFF);
		OLED_Set_Pos(30,5);
		OLED_WrDat(0XFF);
		OLED_Set_Pos(30,6);
		OLED_WrDat(0XFF);
		OLED_Set_Pos(30,7);
		OLED_WrDat(0XFF);
		
		
		
		printf("temp = %d \r\n",MPU_Get_Temperature());
		printf("\r\n���� ��roll:%d, pitch:%d, yaw:%d",(int)(roll),(int)(pitch),(int)(yaw));
		score = BallCtl((int)(roll),(int)(pitch),x1,y1);
		Draw();
	}
    return 0; 
		
}
