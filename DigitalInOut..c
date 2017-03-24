#include "stm32f10x.h"
static unsigned char DI_Data[5];
////////////////////////////////////////////////////////////////////////////////////////////////DI输入获取函数
int GetDI_Data(void)//获取输入的数字信号
{
int value3,value1,value2,Data_ID=0;
value1=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13);
value2=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_14);
value3=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
value2<<=1;
value3<<=2;
Data_ID|=(value1|value2|value3);
return Data_ID;
}
////////////////////////////////////////////获取单个数字输入信号
int GetDI_SingleData(int id)
{
	int state=0;
	switch(id)
	{
	//case 1 :state= GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13);break;//获取输入1的数字信号
		case 1 :state= GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_14);break;//获取输入2的数字信号
		case 2 :state= GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);break;//获取输入3的数字信号
	  case 3 :state= GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2);break;//获取输入3的数字信号		
	  default:break;
	}
	return state;
}
///////////////////////////////////////////////////清零数字输入端口
void Clear_DI(void)
{
GPIO_ResetBits(GPIOA,GPIO_Pin_14);
GPIO_ResetBits(GPIOA,GPIO_Pin_15);
GPIO_ResetBits(GPIOD,GPIO_Pin_2);
}

////////////////////////////////////////////////////////////////////////////////////////////////DO输出设置函数
void SetDO_Data(int data)
{
u16 Bit=1;
	if(Bit&data)
GPIO_SetBits(GPIOB,GPIO_Pin_15);
	else 
GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	Bit<<=1;
		if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_0);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	Bit<<=1;
			if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_1);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_1);
		Bit<<=1;
			if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_2);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_2);
		Bit<<=1;
			if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_3);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_3);
		Bit<<=1;
			if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_4);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		Bit<<=1;
			if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_5);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		Bit<<=1;
			if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_6);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_6);
		Bit<<=1;
			if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_7);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_7);
		Bit<<=1;
			if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_8);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_8);
		Bit<<=1;
			if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_9);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_9);
		Bit<<=1;
			if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_10);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_10);
		Bit<<=1;
			if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_11);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_11);
		Bit<<=1;
			if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_12);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		Bit<<=1;
			if(Bit&data)
GPIO_SetBits(GPIOC,GPIO_Pin_13);
	else 
GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}
////////////////////////////////////////////////
void SetDO_SingleData(int id,int data)
{
	switch(id)
	{
		case 1:{if(data==0)GPIO_ResetBits(GPIOB,GPIO_Pin_15);if(data==1)GPIO_SetBits(GPIOB,GPIO_Pin_15);}break;
		case 2:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_0);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_0);}	break;
		case 3:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_1);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_1);}	break;
		case 4:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_2);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_2);}break;
		case 5:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_3);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_3);}break;
		case 6:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_4);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_4);}break;
		case 7:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_5);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_5);}break;
		case 8:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_6);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_6);}break;
		case 9:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_7);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_7);}break;
		case 10:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_8);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_8);}break;
		case 11:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_9);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_9);}break;
		case 12:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_10);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_10);}break;
		case 13:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_11);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_11);}break;
		case 14:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_12);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_12);}break;
		case 15:{if(data==0)GPIO_ResetBits(GPIOC,GPIO_Pin_13);if(data==1)GPIO_SetBits(GPIOC,GPIO_Pin_13);}break;
		default :break;
	}

}

/////////////////////////////////////////////
unsigned char* ChangeDI_ToCharArray(void)
{
	
int i=0;
DI_Data[0]='#';
DI_Data[4]='%';	
for(i=0;i<3;i++)
DI_Data[i+1]='0';
for(i=0;i<3;i++)
DI_Data[i+1]=GetDI_SingleData(i+1)+'0';
return DI_Data;
}
