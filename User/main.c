#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "font/fonts.h"
#include "bsp_dht11.h"
#include "lcd/bsp_ili9341_lcd.h"
#include "stdio.h"
#include "beep.h"
#include "key.h"
#include "stm32f10x_exti.h"
#include "led.h"
DHT11_Data_TypeDef DHT11_Data;

uint16_t times=0;
char set_t_char[10],set_p_char[10];
char get_t_char[10],get_p_char[10];
u8 set_t=31,set_p=90;  
int get_t,get_p;
void ILI9341_Write_Cmd ( uint16_t usCmd )
{
	* ( __IO uint16_t * ) ( FSMC_Addr_ILI9341_CMD ) = usCmd;
}

void ILI9341_Write_Data ( uint16_t usData )
{
	* ( __IO uint16_t * ) ( FSMC_Addr_ILI9341_DATA ) = usData;
}
uint16_t ILI9341_Read_Data ( void )
{
	return ( * ( __IO uint16_t * ) ( FSMC_Addr_ILI9341_DATA ) );
}

char aaa[100];
void judge(int set_t,int get_t,int set_p,int get_p);
void LCD_show(void);
int main(void)
{	
	
	ILI9341_Init ();  
	led_init();
	ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
	//LCD_SetColors(WHITE,BLACK);
	LCD_show();
	EXTI_Key_Config();
	BEEP_GPIO_Config();
	EXTI_Key_Config();
	delay_init();     //延时函数初始化	  
	uart_init(115200);	 //串口初始化为115200
	DHT11_GPIO_Config();
	delay_ms(500);
	while(1)
	{
		/*调用Read_DHT11读取温湿度，若成功则输出该信息*/
		if( Read_DHT11(&DHT11_Data)==SUCCESS)
		{
			char humidity[80];
			sprintf(humidity,"%d.%d",DHT11_Data.humi_int,DHT11_Data.humi_deci);
			char temperature[80];
			sprintf(temperature,"%d.%d",DHT11_Data.temp_int,DHT11_Data.temp_deci);
			printf("\r\n读取DHT11成功!\r\n\r\n湿度为%d.%d RH ，温度为 %d.%d C\r\n",\
			DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
			get_t = DHT11_Data.temp_int;
			get_p = DHT11_Data.humi_int;
			//ILI9341_DispString_EN ( 20, 20, "humidity" );
			//ILI9341_DispString_EN ( 20, 50,humidity);
			//ILI9341_DispString_EN ( 20, 100, "temperature" );
			//ILI9341_DispString_EN ( 20, 130,temperature);
			delay_ms(2000);		/* 1s 读取一次温度值 */
			judge(set_t,get_t,set_p,get_p);
		}
		/*else
		{
			printf("Read DHT11 ERROR!\r\n");//读取数据失败，串口打印：Read DHT11 ERROR.
			delay_ms(3000);	
		}*/
	}	
}

void judge(int set_t,int get_t,int set_p,int get_p)
{
	if(get_t<set_t){
			LCD_ClearLine(LINE(16));
			LCD_SetTextColor(GREEN);
			sprintf(aaa,"Current temperature:%d.%d C",DHT11_Data.temp_int, DHT11_Data.temp_deci);
			ILI9341_DispStringLine_EN(LINE(9),aaa);
			LED_RED_OFF;
			}
			else{
			LCD_ClearLine(LINE(16));
			LCD_SetTextColor(RED);
			sprintf(aaa,"Current temperature:%d.%d C",DHT11_Data.temp_int, DHT11_Data.temp_deci);
			ILI9341_DispStringLine_EN(LINE(9),aaa);
			ILI9341_DispStringLine_EN(LINE(16),"     !!!WARRING !!!   ");
			printf("Over temperature");
			LED_RED_ON;
			}
			if(get_p<set_p){
			LCD_ClearLine(LINE(17));
			LCD_SetTextColor(GREEN);
			sprintf(aaa,"Current humidity: %d.%d RH",DHT11_Data.humi_int, DHT11_Data.humi_deci);
			ILI9341_DispStringLine_EN(LINE(10),aaa);
			LED_BLUE_OFF;
			}
			else{
			LCD_ClearLine(LINE(17));
			LCD_SetTextColor(BLUE);
			sprintf(aaa,"Current humidity:%d.%d RH",DHT11_Data.humi_int, DHT11_Data.humi_deci);
			LCD_ClearLine(LINE(10));
			ILI9341_DispStringLine_EN(LINE(10),aaa);
			ILI9341_DispStringLine_EN(LINE(17),"     !!!WARRING !!!   ");
			printf("Over humidity");         
			LED_BLUE_ON;				
		}
			if(get_p>=set_p&&get_t>=set_t)
			{
			BEEP( ON );
			}
			else BEEP( OFF );
}
void KEY1_IRQHandler(void)
{
	if(EXTI_GetITStatus(KEY1_INT_EXTI_LINE) != RESET)      
	{
			set_t++;
			if(set_t >= 40){ 
				set_t = 28;
			}
			
			LCD_ClearLine(LINE(6));             
			LCD_SetTextColor(GREEN);            
			sprintf(set_t_char,"Temperature threshold:%d C",set_t);
			LCD_ClearLine(LINE(6));
			ILI9341_DispStringLine_EN(LINE(6),set_t_char); 
			
			EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);  
		}
}
void KEY2_IRQHandler(void)
{
	if(EXTI_GetITStatus(KEY2_INT_EXTI_LINE) != RESET)   
	{
			set_p++;
			if(set_p >= 96){ 
				set_p = 80;
			}

			LCD_ClearLine(LINE(7));
			LCD_SetTextColor(GREEN);
			sprintf(set_p_char,"humidity threshold:%d RH ",set_p);
			LCD_ClearLine(LINE(7));
			ILI9341_DispStringLine_EN(LINE(7),set_p_char);
			EXTI_ClearITPendingBit(KEY2_INT_EXTI_LINE);
	}   
} 
 

void LCD_show(void)
{
	
	LCD_SetTextColor(GREEN);
	sprintf(set_t_char,"Temperature threshold:%d C",set_t);
    LCD_ClearLine(LINE(6));
	ILI9341_DispStringLine_EN(LINE(6),set_t_char);                    
	
	LCD_SetTextColor(GREEN);
	sprintf(set_p_char,"humidity threshold:%d RH",set_p);
    LCD_ClearLine(LINE(7));
	ILI9341_DispStringLine_EN(LINE(7),set_p_char); 
	
	LCD_SetTextColor(GREEN);
	sprintf(get_t_char,"Current temperature:%d C",get_t);
    LCD_ClearLine(LINE(9));
	ILI9341_DispStringLine_EN(LINE(9),get_t_char);                    
	
	LCD_SetTextColor(GREEN);
	sprintf(get_p_char,"Current humidity:%d RH",get_p);
    LCD_ClearLine(LINE(10));
	ILI9341_DispStringLine_EN(LINE(10),get_p_char); 
	
	LCD_ClearLine(LINE(13));
}
