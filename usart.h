#include "stm32f10x.h"
#ifndef _USART_H_
#define _USART_H
int Max(int a,int b);
int CheckADCmd(unsigned char *Cmd);
int CheckDACmd(unsigned char *Cmd);
int CheckDOCmd(unsigned char *Cmd);
int CheckDICmd(unsigned char *Cmd);
int Check_Cmd(unsigned char *Cmd);
int GetDO_Data(unsigned char *Cmd);
int GetDO_ID(unsigned char *Cmd);
u16 GetAO_Data(unsigned char *Cmd);
int GetAO_ID(unsigned char *Cmd);
int GetID(unsigned char *Cmd);
int GetArrayLength(unsigned char *p);
void Clear_Cmd(unsigned char *Cmd);
void Clear_Data(unsigned char *Cmd,int num);
int Check_Complete(unsigned char *Cmd);

void USART1_SendChar(unsigned char Data);
unsigned char USART1_ReceiveData(void);
void USART1_SendData(unsigned char *p,int n);

void USART2_SendChar(unsigned char Data);
unsigned char USART2_ReceiveData(void);
void USART2_SendData(unsigned char *p,int n);

void USART3_SendChar(unsigned char Data);
unsigned char USART3_ReceiveData(void);
void USART3_SendData(unsigned char *p,int n);
	
void USART2_SendMessage(unsigned char a[8][8],int dim,int num);
void USART3_SendMessage(unsigned char a[8][8],int dim,int num);
void USART1_SendMessage(unsigned char a[8][8],int dim,int num);
#endif
