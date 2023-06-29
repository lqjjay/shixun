
#include "stm32f10x.h"
#include "led.h"

void led_init(void)
{
	  GPIO_InitTypeDef  GPIO_InitStructure;//定义结构
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开时钟
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0 | GPIO_Pin_5; // PB 1
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置频率
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置模式
	  GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化
	
	  LED_BLUE_OFF;
	  LED_GREEN_OFF;
	  LED_RED_OFF;
}
 
