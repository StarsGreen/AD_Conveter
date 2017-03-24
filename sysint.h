#ifndef _SYSINT_H
#define _SYSINT_H
//#include "stm32f10x.h"
void delay_ms(int ms);
void delay_us(int us);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void); 
void USART_Configuration(void); 
void DMA_Configuration(void);
void DAC_Configuration(void);
void ADC_Configuration(void);
void IniADvalue(void);///////////;
void IWDG_Init(void);
void IWDG_Feed(void);
#endif
