#include "stm32f10x.h"
#ifndef _DAC_H_
#define _DAC_H
void DAC_SetOutPutValue(u16 value);//�ڲ�DAC��ʹ�ã��ⲿDAC����ʹ��
void WriteDAC1(u16  Data) ;//�ⲿDAC��ʹ��
void WriteDAC2(u16  Data) ;//�ⲿDAC��ʹ��
void WriteDAC(u16 ID,u16 Data) ;//DACѡ��
#endif
