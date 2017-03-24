#include "stm32f10x.h"
#include "sysint.h"
#include "interrupt.h"
extern u16 Data_Ave[8];
extern u16 AD_ReadValue[15][8] ;
//extern u16 AD_ReadValue[8] ;
static u16 AD_VolValue[8][15];
//static u16 AD_VolValue[8];
extern unsigned char CharArray[8][8];
////////////////////////////////////////TEST
//----------------------------------
void Sort(u16 *data,int num)
{
u16 t;
int i,j;
for( j=0;j<num;j++)
for( i=0;i<num-j;i++)
if(*(data+i)>*(data+i+1))
{ 
t=*(data+i);
*(data+i)=*(data+i+1);  
*(data+i+1)=t; 
}
}
//------------------------------------
u16 Average(u16 * value,int num)//num=50
{
u16 Temp[8],sum=0;
int j,i;
Sort(value,num);
for(j=0;j<num-2;j++)		
	{
	Temp[j]=*(value+j+1);
	}
for(i=0;i<num-2;i++)
sum+=*(Temp+i);
return sum/(num-2);
}
//////////////////////////////////////////////////////
 void Change_ToVolt(u16 value[10][8],int num,int dim)//num=50,dim=8
{
int j=0,i=0;
for( j=0;j<dim;j++)
for( i=0;i<num;i++)
AD_VolValue[j][i]=value[i][j]*3300/4096;
}
//////////////////////////////////////////
void Change_ToChar(u16 *value,int num)
{
int i=0;
for(i=0;i<num;i++)	
	{
  CharArray[i][0]='#';
	CharArray[i][1]=(*(value+i))/1000+'0';
	CharArray[i][2]='.';
  CharArray[i][3]=((*(value+i))/100)%10+'0';	
  CharArray[i][4]=((*(value+i))%100)/10+'0';	
  CharArray[i][5]=*(value+i)%10+'0';
	CharArray[i][6]='%';
	CharArray[i][7]='\r';
	}
}
////----------------------------------------
//void Change_ToChar(u16 *value,int num)
//{
//int i=0;
//for(i=0;i<num;i++)	
//	{
//  CharArray[i][0]='#';
//  CharArray[i][5]='%';
//  CharArray[i][1]=1+'0';
//  CharArray[i][2]=((150)%100)/10+'0';
//  CharArray[i][3]=((150)/100)%10+'0';
//	CharArray[i][4]=5+'0';
//	CharArray[i][6]='\r';
//	}
//}
///////////////////////////////////////////////////
void StartAD(void)
{
ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
///////////////////////////////////////////////////ֹͣAD
void StopAD(void)
{
ADC_SoftwareStartConvCmd(ADC1, DISABLE);
}
/////////////////////////////////////////////////////
void DataPro(void)
{
int i;
Change_ToVolt(AD_ReadValue,10,8);
for(i=0;i<8;i++)	
	{
Data_Ave[i]=Average(AD_VolValue[i],10);
	}
Change_ToChar(Data_Ave,8);
}
///////////////////////////////////////////////////
//void DataPro(void)
//{
////int i;
//Change_ToVolt(AD_ReadValue,8);
//Change_ToChar(AD_VolValue,8);
//}

