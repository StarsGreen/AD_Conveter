#include "stm32f10x.h"
#include "sysint.h"
extern unsigned char USART1_CmdData[15];
extern int CmdCharNum1,CmdCharNum2;

/////////////////////////////////////////////////////////串口1发送单字符
void USART1_SendChar(unsigned char Data)
{
 USART_GetFlagStatus(USART1,USART_FLAG_TC);
		USART_SendData(USART1,Data);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET){}
	USART_ClearFlag(USART1,USART_FLAG_TC);
}
/////////////////////////////////////////////////////////串口1发送一维字符数组
void USART1_SendData(unsigned char *p,int n)
{
int i=0;
for(i=0;i<n;i++)
	{	
 USART_GetFlagStatus(USART1,USART_FLAG_TC);
		USART_SendData(USART1,*(p+i));
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET){}
//			    delay_us(2);
	USART_ClearFlag(USART1,USART_FLAG_TC);
	}
}
//////////////////////////////////////串口1接受字符
unsigned char USART1_ReceiveData(void)
{
unsigned char RxBuffer;
RxBuffer = USART_ReceiveData(USART1);
while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)!=RESET){};	
return  RxBuffer;
}

////////////////////////////////////////////////////////串口1发送二维字符数组
void USART1_SendMessage(unsigned char a[8][8],int dim,int num)
{
int j=0;
for(j=0;j<dim;j++)
USART1_SendData(a[j],num);
}
/////////////////////////////////////////////////////////串口2发送单字符
void USART2_SendChar(unsigned char Data)
{
 USART_GetFlagStatus(USART2,USART_FLAG_TC);
		USART_SendData(USART2,Data);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET){}
			  //  delay_us(2);
	USART_ClearFlag(USART2,USART_FLAG_TC);
}
/////////////////////////////////////////////////////////串口2发送一维字符数组
void USART2_SendData(unsigned char *p,int n)
{
int i=0;
for(i=0;i<n;i++)
	{	
 USART_GetFlagStatus(USART2,USART_FLAG_TC);
		USART_SendData(USART2,*(p+i));
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET){}
			   // delay_us(2);
	USART_ClearFlag(USART2,USART_FLAG_TC);
	}
}
//////////////////////////////////////串口2接受字符
unsigned char USART2_ReceiveData(void)
{
unsigned char RxBuffer;
RxBuffer = USART_ReceiveData(USART2);
while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE)!=RESET){};	
return  RxBuffer;
}
////////////////////////////////////////////////////////串口2发送二维字符数组
void USART2_SendMessage(unsigned char a[8][8],int dim,int num)
{
int j=0;
for(j=0;j<dim;j++)
USART2_SendData(a[j],num);
}
//////////////////////////////////////串口3接受字符
unsigned char USART3_ReceiveData(void)
{
unsigned char RxBuffer;
RxBuffer = USART_ReceiveData(USART3);
while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE)!=RESET){};	
return  RxBuffer;
}
/////////////////////////////////////////////////////////串口1发送单字符
void USART3_SendChar(unsigned char Data)
{
 USART_GetFlagStatus(USART3,USART_FLAG_TC);
		USART_SendData(USART3,Data);
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET){}
			   // delay_us(2);
	USART_ClearFlag(USART3,USART_FLAG_TC);
}
/////////////////////////////////////////////////////////串口3发送一维字符数组
void USART3_SendData(unsigned char *p,int n)
{
int i=0;
for(i=0;i<n;i++)
	{	
 USART_GetFlagStatus(USART3,USART_FLAG_TC);
		USART_SendData(USART3,*(p+i));
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET){}
						 //   delay_us(2);
	USART_ClearFlag(USART3,USART_FLAG_TC);
	}
}
////////////////////////////////////////////////////////串口3发送二维字符数组
void USART3_SendMessage(unsigned char a[8][8],int dim,int num)
{
int j=0;
for(j=0;j<dim;j++)
USART3_SendData(a[j],num);
}
///////////////////////////////////////////////////////获取字符串的长度
int GetArrayLength(unsigned char *p)
{
int i=0,num=0;
for(i=0;i<15;i++)
	{
	if(*(p+i)!=0)num++;
	}
return num;
}
///////////////////////////////////////////////////////取最大值
int Max(int a,int b)
{
	return a>b?a:b;
}
///////////////////////////////////////////////////////检查命令完整性
int Check_Complete(unsigned char *Cmd)
{
if((*Cmd=='#')&&(*(Cmd+GetArrayLength(Cmd)-1)=='%'))
return 1;
else return 0;
}
///////////////////////////////////////////////////////检查AI命令
int CheckAICmd(unsigned char *Cmd)
{
if((*(Cmd+1)=='I')&&(*(Cmd+2)=='D')&&(*(Cmd+4)=='#')&&(*(Cmd+5)=='A')&&(*(Cmd+6)=='I'))
return 1;
else return 0;
}
///////////////////////////////////////////////////////检查AO命令
int CheckAOCmd(unsigned char *Cmd)
{
if((*(Cmd+1)=='I')&&(*(Cmd+2)=='D')&&(*(Cmd+4)=='#')&&(*(Cmd+5)=='A')&&(*(Cmd+6)=='O')&&(*(Cmd+7)=='#')&&(*(Cmd+9)=='#'))
return 2;
else return 0;
}
///////////////////////////////////////////////////////检查DO命令
int CheckDOCmd(unsigned char *Cmd)
{
if((*(Cmd+1)=='I')&&(*(Cmd+2)=='D')&&(*(Cmd+4)=='#')&&(*(Cmd+5)=='D')&&(*(Cmd+6)=='O')&&(*(Cmd+7)=='#')&&(*(Cmd+9)=='#'))
return 3;
else return 0;
}
////////////////////////////////////////////////////////检查DI命令
int CheckDICmd(unsigned char *Cmd)
{
if((*(Cmd+1)=='I')&&(*(Cmd+2)=='D')&&(*(Cmd+4)=='#')&&(*(Cmd+5)=='D')&&(*(Cmd+6)=='I'))
return 4;
else return 0;
}
////////////////////////////////////////////////////////检查命令，并返回特征码
int Check_Cmd(unsigned char *Cmd)
{
	int Cmd_Flag=0;
switch(*(Cmd+5))
	{
	case 'A':if(*(Cmd+6)=='I')Cmd_Flag=CheckAICmd(Cmd);if(*(Cmd+6)=='O')Cmd_Flag=CheckDICmd(Cmd);break;
	case 'D':if(*(Cmd+6)=='I')Cmd_Flag=CheckDICmd(Cmd);if(*(Cmd+6)=='O')Cmd_Flag=CheckDOCmd(Cmd);break;
	default:break;
	}
	return Cmd_Flag;
}
/////////////////////////////////////////////////////////清除命令
void Clear_Cmd(unsigned char *Cmd)
{
int i;
for(i=0;i<15;i++)
*(Cmd+i)=0;
}
/////////////////////////////////////////////////////////清除数据
void Clear_Data(unsigned char *Cmd,int num)
{
int i;
for(i=0;i<num;i++)
*(Cmd+i)=0;
}
////////////////////////////////////////////////////////获取命令字符串的ID
int GetID(unsigned char *Cmd)
{
return (*(Cmd+3)-'0');
}
//////////////////////////////////////////////////////获取命令中AO的ID
int GetAO_ID(unsigned char *Cmd)
{
return *(Cmd+8)-'0';
}
//////////////////////////////////////////////////////获取命令字符串的AO的数据
u16 GetAO_Data(unsigned char *Cmd)
{
	unsigned int  AO_Data[4],Temp=0;
    AO_Data[0]= *(Cmd+10)-'0';
	   AO_Data[1]= *(Cmd+12)-'0';
	    AO_Data[2]= *(Cmd+13)-'0';
	     AO_Data[3]= *(Cmd+14)-'0';
	Temp=AO_Data[0]*1000+AO_Data[1]*100+AO_Data[2]*10+AO_Data[3];	
	return (Temp/1000)/3.3*4096;
}
//////////////////////////////////////////////////////获取命令中DO的ID
int GetDO_ID(unsigned char *Cmd)
{
return (*(Cmd+8)-'0');
}
/////////////////////////////////////////////////////获取命令字符串的DO的数据
int GetDO_Data(unsigned char *Cmd)
{
if( *(Cmd+10)=='T')return 1;
	else return 0;
}
