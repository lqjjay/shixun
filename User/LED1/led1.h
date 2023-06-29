#ifndef __LED_H
#define __LED_H

#define digitalToggle(p,i) {p->ODR ^=i;} //Êä³ö·´×ª×´Ì¬

#define LED_BLUE_ON     GPIO_ResetBits(GPIOB,GPIO_Pin_1);
#define LED_BLUE_OFF    GPIO_SetBits(GPIOB,GPIO_Pin_1);
#define LED_BLUE_TOGGLE		 digitalToggle(GPIOB,GPIO_Pin_1);

#define LED_GREEN_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_0);
#define LED_GREEN_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_0);
#define LED_GREEN_TOGGLE		 digitalToggle(GPIOB,GPIO_Pin_0);

#define LED_RED_ON      GPIO_ResetBits(GPIOB,GPIO_Pin_5);
#define LED_RED_OFF     GPIO_SetBits(GPIOB,GPIO_Pin_5);
#define LED_RED_TOGGLE		 digitalToggle(GPIOB,GPIO_Pin_5);

void led_init(void);


#endif

