#include "stm32f10x.h"
#ifndef _ADC_H
#define _ADC_H
void Sort(u16  *data,int num);
u16  Average(u16  * value,int num);
//void ChangeToVolt(u16  *data,int num,int dim);
  void Change_ToVolt(u16 value[10][8],int num,int dim);
 void GetAve(u16 *value,int num,int dim);
 void Change_ToChar(u16 *value,int num);
 void DataPro(void);
 void StartAD(void);
 void GetADValue(void);
 void Init_ADCin(void);
#endif
