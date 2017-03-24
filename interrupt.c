#include "stm32f10x.h"
#include "sysint.h"
#include "usart.h"
unsigned char USART1_CmdData[15],USART2_CmdData[15],USART3_Data;
static u16 CmdCharNum1=0,CmdCharNum2=0,CmdCharNum3=0;
/////////////////////////////////////////////////////////////////
void USART1_IRQHandler(void)
{ 
if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
USART1_CmdData[CmdCharNum1++]= USART_ReceiveData(USART1);
if(USART1_CmdData[CmdCharNum1-1]=='%'||(CmdCharNum1>=15))
	CmdCharNum1=0;
	}
USART_ClearITPendingBit(USART1,  USART_IT_RXNE);//清除中断标志
}
/////////////////////////////////////////////////////////////////
void USART2_IRQHandler(void)
{
if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{
//USART2_CmdData[CmdCharNum2]= USART_ReceiveData(USART2);
//		CmdCharNum2++;
//		if(USART2_CmdData[CmdCharNum2]=='%')
//		{
//			CmdCharNum2=0;
//			USART1_SendData(USART2_CmdData,GetArrayLength(USART2_CmdData));
//			Clear_Cmd(USART2_CmdData);
//		}
		USART2_SendChar('a');
		USART2_SendChar('b');
		USART2_SendChar('\r');
	}
USART_ClearITPendingBit(USART2,  USART_IT_RXNE);//清除中断标志
}

/////////////////////////////////////////////////////////
void USART3_IRQHandler(void)
{ 
if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
	{
//		USART3_CmdData[CmdCharNum3]= USART_ReceiveData(USART3);
//		CmdCharNum3++;
//		if(GetArrayLength(USART3_CmdData)==64)
//		{
//			CmdCharNum3=0;
//	  }
		USART3_Data=USART_ReceiveData(USART3);
		USART1_SendChar(USART3_Data);
    USART3_Data=0;
}
USART_ClearITPendingBit(USART3,  USART_IT_RXNE);//清除中断标志

}
