#ifndef __DHT11_H
#define	__DHT11_H

#include "stm32f10x.h"
#include "delay.h"

#define HIGH  1
#define LOW   0

#define DHT11_CLK     RCC_APB2Periph_GPIOE
#define DHT11_PIN     GPIO_Pin_6                  
#define DHT11_PORT		GPIOE 

//���κ꣬��������������һ��ʹ��,����ߵ�ƽ��͵�ƽ
#define DHT11_DATA_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_6)
 //��ȡ���ŵĵ�ƽ
#define  DHT11_DATA_IN()	   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)

typedef struct
{
	uint8_t  humi_int;		//ʪ�ȵ���������
	uint8_t  humi_deci;	 	//ʪ�ȵ�С������
	uint8_t  temp_int;	 	//�¶ȵ���������
	uint8_t  temp_deci;	 	//�¶ȵ�С������
	uint8_t  check_sum;	 	//У���
		                 
}DHT11_Data_TypeDef;

void DHT11_GPIO_Config(void);
static void DHT11_Mode_IPU(void);
static void DHT11_Mode_Out_PP(void);
uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data);
static uint8_t Read_Byte(void);

#endif /* __DHT11_H */






