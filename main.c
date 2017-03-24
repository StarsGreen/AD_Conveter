#include "stm32f10x.h"
#include "sysint.h"
#include "adc.h"
#include "dac.h"
#include "dio.h"
#include "usart.h"
#include "interrupt.h"
#include <string.h> 
#include <stdio.h> 
#define ID  0X03
extern unsigned char USART1_CmdData[15],USART3_CmdData[64],USART3_Data;
u16 Data_Ave[8];
unsigned char CharArray[8][8];
unsigned char Test[2][2]={{'a','d'},{'f','l'}};
unsigned char OK[3]={'O','K','\r'};
unsigned char NO[3]={'N','0','\r'};
int main(void)
{
	//int i;
	int Cmd_FlagNum=0,id=0;
	delay_ms(100);
  RCC_Configuration();       //ϵͳʱ�ӳ�ʼ��
  GPIO_Configuration();      //��ʼ��IO��
  NVIC_Configuration();      //��ʼ���ж�
  USART_Configuration();     //��ʼ������
	DMA_Configuration();       //DMA��ʼ��
  ADC_Configuration();       //ADC��ʼ��
	IWDG_Init();      //���Ź���ʼ��
	StartAD();
	delay_ms(100);
while(1)       
{
	IWDG_Feed();
	if((GetArrayLength( USART1_CmdData)==8||GetArrayLength( USART1_CmdData)==15||GetArrayLength( USART1_CmdData)==12)&&( Check_Complete(USART1_CmdData)))
{
		id=GetID(USART1_CmdData);
		Cmd_FlagNum=Check_Cmd(USART1_CmdData);
	if(id==ID)
	{
	switch(Cmd_FlagNum)
	{
	case 1:DataPro();USART1_SendMessage(CharArray,8,8);USART1_SendChar('\r');break;//break;USART1_SendData(NO,3);
	case 2:WriteDAC(GetAO_ID(USART1_CmdData),GetAO_Data(USART1_CmdData));break;
	case 3:SetDO_SingleData(GetDO_ID(USART1_CmdData),GetDO_Data(USART1_CmdData));break;
	case 4:USART1_SendData(ChangeDI_ToCharArray(),5);USART1_SendChar('\r');break;
	default:break;
	}
  Clear_Cmd(USART1_CmdData);
  }
	else 
	{
	USART3_SendData(USART1_CmdData,GetArrayLength( USART1_CmdData));
	Clear_Cmd(USART1_CmdData);
	}
}
}
}
