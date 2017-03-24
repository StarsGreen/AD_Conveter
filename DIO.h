#ifndef _DIO_H
#define _DIO_H
//void SetDO0_Data(int data);
//void SetDO1_Data(int data);
//void SetDO2_Data(int data);
//void SetDO3_Data(int data);
//void SetDO4_Data(int data);
//void SetDO5_Data(int data);
//void SetDO6_Data(int data);
//void SetDO7_Data(int data);
//void SetDO8_Data(int data);
//void SetDO9_Data(int data);
//void SetDO10_Data(int data);
//void SetDO11_Data(int data);
//void SetDO12_Data(int data);
//void SetDO13_Data(int data);
//void SetDO14_Data(int data);
//////////////////////////////////
void SetDO_Data(int data);//DO输出设置函数
void SetDO_SingleData(int id,int data);//单个DO设置状态
void Clear_DI(void);//清除DIO口
//////////////////////////////////
int GetDI_Data(void);//获取输入的数字信号
int GetDI_SingleData(int id);//获取单个IO口电平
unsigned char* ChangeDI_ToCharArray(void);//将DI状态数据转化为字符
#endif
