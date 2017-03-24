#include "stm32f10x.h"
#include "sysint.h"
#define DA1_CS1  GPIO_SetBits(GPIOB,GPIO_Pin_7);
#define DA1_CS0  GPIO_ResetBits(GPIOB,GPIO_Pin_7);
#define DA1_CLK1  GPIO_SetBits(GPIOB,GPIO_Pin_6);
#define DA1_CLK0  GPIO_ResetBits(GPIOB,GPIO_Pin_6);
#define DA1_DIN1  GPIO_SetBits(GPIOB,GPIO_Pin_5);
#define DA1_DIN0  GPIO_ResetBits(GPIOB,GPIO_Pin_5);
/////////////////////////////////////////////////
#define DA2_CS1  GPIO_SetBits(GPIOB,GPIO_Pin_14);
#define DA2_CS0  GPIO_ResetBits(GPIOB,GPIO_Pin_14);
#define DA2_CLK1  GPIO_SetBits(GPIOB,GPIO_Pin_13);
#define DA2_CLK0  GPIO_ResetBits(GPIOB,GPIO_Pin_13);
#define DA2_DIN1  GPIO_SetBits(GPIOB,GPIO_Pin_12);
#define DA2_DIN0  GPIO_ResetBits(GPIOF,GPIO_Pin_12);;
//---------------------------
void DAC_SetOutPutValue(u16 value)
{
DAC_SetChannel1Data(DAC_Align_12b_R, value);//设置DAC值
//DAC_GetDataOutputValue(DAC_Channel_1);//读取前面设置DAC的值
}
/////////////////////////////////////////////////写ADC1的数据
void WriteDAC1(u16  Data) 
{ 
	int i;
	u16 Bit=0x8000;
	DA1_CS0;
	DA1_CS1;
	DA1_CS0;
	delay_us(1);
	DA1_DIN0;
	DA1_CLK0;
	for(i=0;i<8;i++)
	{
	DA1_CLK1;
	delay_us(1);
	DA1_CLK0;
	}
	for(i=0;i<16;i++)
	{
	DA1_CLK1;
	if(Bit&Data) DA1_DIN1
		else  DA1_DIN0;
	Bit>>=1;
	DA1_CLK0;
	delay_us(1);
	}
	
} 
/////////////////////////////////////////////////写ADC2的数据
void WriteDAC2(u16  Data) 
{ 
	int i;
	u16 Bit=0x80;
	DA2_CS0;
	DA2_CS1;
	DA2_CS0;
	delay_us(1);
	DA2_DIN0;
	DA2_CLK0;
	for(i=0;i<8;i++)
	{
	DA2_CLK1;
	delay_us(1);
	DA2_CLK0;
	}
	for(i=0;i<16;i++)
	{
	DA2_CLK1;
	if(Bit&Data) DA2_DIN1
		else  DA2_DIN0;
	Bit>>=1;
	DA2_CLK0;
	delay_us(1);
	}
}
///////////////////////////////////////////////写ADC数据
void WriteDAC(u16 ID,u16 Data) 
{
if(ID==1)WriteDAC1(Data);
if(ID==2)WriteDAC2(Data);
}
