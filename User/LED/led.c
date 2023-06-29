
#include "stm32f10x.h"
#include "led.h"

void led_init(void)
{
	  GPIO_InitTypeDef  GPIO_InitStructure;//����ṹ
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//��ʱ��
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0 | GPIO_Pin_5; // PB 1
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����Ƶ��
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//����ģʽ
	  GPIO_Init(GPIOB,&GPIO_InitStructure);//��ʼ��
	
	  LED_BLUE_OFF;
	  LED_GREEN_OFF;
	  LED_RED_OFF;
}
 
