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
void SetDO_Data(int data);//DO������ú���
void SetDO_SingleData(int id,int data);//����DO����״̬
void Clear_DI(void);//���DIO��
//////////////////////////////////
int GetDI_Data(void);//��ȡ����������ź�
int GetDI_SingleData(int id);//��ȡ����IO�ڵ�ƽ
unsigned char* ChangeDI_ToCharArray(void);//��DI״̬����ת��Ϊ�ַ�
#endif
