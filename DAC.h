#include "stm32f10x.h"
#ifndef _DAC_H_
#define _DAC_H
void DAC_SetOutPutValue(u16 value);//内部DAC可使用，外部DAC不可使用
void WriteDAC1(u16  Data) ;//外部DAC可使用
void WriteDAC2(u16  Data) ;//外部DAC可使用
void WriteDAC(u16 ID,u16 Data) ;//DAC选择
#endif
