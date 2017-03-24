#include "stm32f10x.h"
/*����ADC1_DR_Address  Ϊ((u32)0x40012400+0x4c) ����Ϊ���ADת������ļĴ����ĵ�ַ����0x4001244c*/ 
#define  ADC1_DR_Address    ((u32)0x40012400+0x4c)  
///*�������ADC_ConvertedValue,��AD1ͨ��10ת��������*/
//__IO uint16_t ADC_ConvertedValue;
#define N 10 //ÿͨ����50��
#define M 8 //Ϊ8��ͨ��
u16 AD_ReadValue[N][M] ;
//u16 AD_ReadValue[M] ;
/////////////////////////////////////////////test
//void IniADvalue(void)
//{
//	int j;
////for(i=0;i<5;i++)
//	for(j=0;j<8;j++)
//	 AD_ReadValue[j]=152*j;
//}
/////////////////////////////////////////////
void delay_ms(int ms)
{
	int i,j;
for(i=0;i<ms;i++)
	for(j=0;j<12000;j++);
}
//////////////////////////////////////////////
void delay_us(int us)
{
	int i,j;
for(i=0;i<us;i++)
	for(j=0;j<10;j++);
}

///////////////////////////////////////
void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;      //ö�ٱ������������ʱ�ӵ�����״̬
  RCC_DeInit();                   //RCCϵͳ���ã�����DebugĿ��
  RCC_HSEConfig(RCC_HSE_ON);                 //ʹ�ܸ���ʱ��ԴHSE  
  HSEStartUpStatus = RCC_WaitForHSEStartUp();    //�ȴ�HSE�ȶ�
  if(HSEStartUpStatus == SUCCESS)
  {    
    RCC_HCLKConfig(RCC_SYSCLK_Div1);         // HCLK = SYSCLK
    RCC_PCLK2Config(RCC_HCLK_Div1);          // PCLK2 = HCLK
    RCC_PCLK1Config(RCC_HCLK_Div2);         ///PCLK1 = HCLK/2
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){}
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while(RCC_GetSYSCLKSource() != 0x08){}
  }
SystemInit();
   	// Enable FSMC, GPIOD, GPIOE clocks
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_ADC1 |RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
   	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_DAC|RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART1,2��GPIOAʱ��
	  RCC_ADCCLKConfig(RCC_PCLK2_Div8); //72M/8=9
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //enable DMA request
}
//------------------------------------------------------------------
//��������void GPIO_Configuration()
//���������null
//���ز�����null
//˵����GPIO��ʼ������
//------------------------------------------------------------------
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //GPIO��ʼ���ṹ������
	//////////////////////////////////////////////////////////////////////////////////////��ӳ��
//	GPIO_AFIODeInit();
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	///////////////////////////////////////////////////////////////////////////////////////����ͨ��1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;          //TX1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);      //A�˿�
	
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;          //RX1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOA, &GPIO_InitStructure);      //A�˿�
	
///////////////////////////////////////////////////////////////////////////////����ͨ��	USART2
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;          //TX2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);      //A�˿�
	
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;          //RX2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOA, &GPIO_InitStructure);      //A�˿�
///////////////////////////////////////////////////////////////////////////////////////����ͨ��3
		  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;          //TX3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);      //A�˿�
	
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;          //RX3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOB, &GPIO_InitStructure);      //A�˿�
////////////////////////////////////////////////////////////////////////////////////////GPIO�ڵ����á�������ģ������
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;    //ģ������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOA, &GPIO_InitStructure);      //A�˿�
		
  	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;    //ģ������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOB, &GPIO_InitStructure);      //B�˿�
	////////////////////////////////////////////////////////////////////////////////////////GPIO�ڵ����á���������������
//	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;         
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //��������
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
//	  GPIO_Init(GPIOA, &GPIO_InitStructure);      //A�˿�
		
  	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOD, &GPIO_InitStructure);      //D�˿�	
			////////////////////////////////////////////////////////////////////////////////////////GPIO�ڵ����á��������������
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12;         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;    //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOC, &GPIO_InitStructure);      //C�˿�
		
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;    //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOB, &GPIO_InitStructure);      //C�˿�
////////////////////////////////////////////////////////////////////////////////////////GPIO�ڵ����á�������DAC���
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14;         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;  //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOB, &GPIO_InitStructure);      //A�˿�

}
//------------------------------------------------------------------
//��������void NVIC_Configuration()
//���ز�����null
//˵����NVIC��ʼ������
//���������null
//------------------------------------------------------------------
void NVIC_Configuration(void)
{              
  NVIC_InitTypeDef NVIC_InitStructure;       //NVIC��ʼ���ṹ������

//////////////////////////////////////////////�����ж�����
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;         //���ô���2�ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ� 0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    //�����ȼ�Ϊ0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //ʹ��
  NVIC_Init(&NVIC_InitStructure);	
//////////////////////////////////////////////�����ж�����
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;         //���ô���3�ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ� 0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =2 ;    //�����ȼ�Ϊ0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //ʹ��
  NVIC_Init(&NVIC_InitStructure);	
	//////////////////////////////////////////////�����ж�����
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;         //���ô���1�ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ� 0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =0 ;    //�����ȼ�Ϊ0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //ʹ��
  NVIC_Init(&NVIC_InitStructure);	
/////////////////////////////////////////////////////��ʱ���ж�����
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;           //���ö�ʱ��4ȫ���ж�
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;        //��ռ���ȼ� 1
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            //�����ȼ�Ϊ0
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ��
//  NVIC_Init(&NVIC_InitStructure);
//	///////////////////////////////////////////////////��ʱ���ж�����
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;           //���ö�ʱ��5ȫ���ж�
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;        //��ռ���ȼ� 1
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            //�����ȼ�Ϊ0
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ��
//  NVIC_Init(&NVIC_InitStructure);
}
//------------------------------------------------------------------
//��������void USART_Configuration()
//���������null
//���ز�����null
//˵��:���ڳ�ʼ������
//------------------------------------------------------------------
void USART_Configuration(void)
	{
  USART_InitTypeDef USART_InitStructure;                   //���ڳ�ʼ���ṹ������
  USART_ClockInitTypeDef USART_ClockInitStruct;
  USART_InitStructure.USART_BaudRate = 9600;      //���ò�����Ϊ115200bps
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //����λ8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;   //ֹͣλ1λ
  USART_InitStructure.USART_Parity = USART_Parity_No;    //��У��λ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //��Ӳ������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;     //���ܺͷ���ģʽ����
		
  USART_ClockInitStruct.USART_Clock=USART_Clock_Disable;      //����ʱ�ӽ�ֹ
  USART_ClockInitStruct.USART_CPOL=USART_CPOL_Low;        //���ݵ͵�ƽ��Ч
  USART_ClockInitStruct.USART_CPHA=USART_CPHA_2Edge;    //����CPHAʹ�����ڵ�2�����ص�ʱ�򱻲���
  USART_ClockInitStruct.USART_LastBit=USART_LastBit_Disable;  // �������һλ,ʹ��Ӧ��ʱ�����岻���������SCLK����
		
 USART_ClockInit(USART1, &USART_ClockInitStruct);      //����USART��ʱ����ص�����
  USART_Init(USART1, &USART_InitStructure);       //���ô��ڲ�������
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);       //ʹ�ܽ����ж�
//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);    //ʹ�ܷ��ͻ�����ж�
//USART_ITConfig(USART1, USART_IT_TC, ENABLE);    //ʹ�ܷ�������ж�
  USART_ClearFlag(USART1,USART_FLAG_TC);         //���������ɱ�־λ
  USART_Cmd(USART1, ENABLE); 
	
  USART_ClockInit(USART2, &USART_ClockInitStruct);      //����USART��ʱ����ص�����
  USART_Init(USART2, &USART_InitStructure);       //���ô��ڲ�������
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);       //ʹ�ܽ����ж�
//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);    //ʹ�ܷ��ͻ�����ж�
//USART_ITConfig(USART1, USART_IT_TC, ENABLE);    //ʹ�ܷ�������ж�
  USART_ClearFlag(USART2,USART_FLAG_TC);         //���������ɱ�־λ
  USART_Cmd(USART2, ENABLE);         //ʹ�ܴ���2
		
	USART_ClockInit(USART3, &USART_ClockInitStruct);      //����USART��ʱ����ص�����
  USART_Init(USART3, &USART_InitStructure);       //���ô��ڲ�������
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);       //ʹ�ܽ����ж�
//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);    //ʹ�ܷ��ͻ�����ж�
//USART_ITConfig(USART1, USART_IT_TC, ENABLE);    //ʹ�ܷ�������ж�
  USART_ClearFlag(USART3,USART_FLAG_TC);         //���������ɱ�־λ
  USART_Cmd(USART3, ENABLE);         //ʹ�ܴ���3
}
	//------------------------------------------------------------------
//��������void AD_Configuration()
//���������null
//���ز�����null
//˵��:ad��ʼ������
//------------------------------------------------------------------
void ADC_Configuration(void)
{
ADC_InitTypeDef ADC_InitStructure;
ADC_DeInit(ADC1);//������ADC1��ȫ���Ĵ�������Ϊȱʡֵ
ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
ADC_InitStructure.ADC_ScanConvMode=ENABLE;//ģ��ת��������ɨ��ģʽ
ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;//ģ��ת������������ת��ģʽ
ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//�ⲿ����ת���ر�
ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//ADC�����Ҷ���
ADC_InitStructure.ADC_NbrOfChannel=M;//˳����й���ת����ADCͨ������Ŀ
ADC_Init(ADC1,&ADC_InitStructure);
//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
//����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ�� //ADC1,ADCͨ��x,�������˳��ֵΪy,����ʱ��Ϊ239.5���� 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5 );
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 3, ADC_SampleTime_239Cycles5 ); 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 4, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 5, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 6, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 7, ADC_SampleTime_239Cycles5 ); 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 8, ADC_SampleTime_239Cycles5 );
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 7, ADC_SampleTime_239Cycles5 );
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 8, ADC_SampleTime_239Cycles5 );
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 9, ADC_SampleTime_239Cycles5 ); 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 10, ADC_SampleTime_239Cycles5 );
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 11, ADC_SampleTime_239Cycles5 ); 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 12, ADC_SampleTime_239Cycles5 );  
ADC_DMACmd(ADC1, ENABLE);   // ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����
ADC_Cmd(ADC1, ENABLE); //ʹ��ָ����ADC1  
ADC_ResetCalibration(ADC1); //��λָ����ADC1��У׼�Ĵ���
while(ADC_GetResetCalibrationStatus(ADC1)); //��ȡADC1��λУ׼�Ĵ�����״̬,����״̬��ȴ�   
ADC_StartCalibration(ADC1); //��ʼָ��ADC1��У׼״̬  
while(ADC_GetCalibrationStatus(ADC1)); //��ȡָ��ADC1��У׼����,����״̬��ȴ� 
}
	//------------------------------------------------------------------
//��������void DMA_Configuration()
//���������null
//���ز�����null
//˵��:ad��ʼ������
//------------------------------------------------------------------
void DMA_Configuration(void)
{
	DMA_InitTypeDef  DMA_InitStructure; 
	DMA_DeInit(DMA1_Channel1);  /* ����DMA�йصļĴ������ҳ�ʼֵ */  
	DMA_InitStructure.DMA_PeripheralBaseAddr =ADC1_DR_Address ;   /*����DMA�������ַ, �����ADC1_DR_Address ���û��Լ�����ģ���Ϊ���ת������ļĴ��� ���������þ��Ǹ���DMAȡ���͵�ADC1_DR_Address ������ȡ��*/ 
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32)&AD_ReadValue;  /*�����ڴ����ַ��������DMAҪ����AD��ȡ�������ŵ�ADC_Value�� */  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;    /*����AD������Ϊ���ݴ������Դ��������DMA�ǽ�AD�е�����ȡ���ŵ��ڴ��У����ܷ�����*/  
  DMA_InitStructure.DMA_BufferSize = M*N;   /*ָ��DMAͨ����DMA����Ĵ�С,������DMA���ټ����ڴ�ռ�*/ 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   /*�趨�Ĵ�����ַ�̶���������DMA��ֻ�ӹ̶���һ���ط�ȡ��*/  
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;     /*�趨�ڴ��ַ�̶�����ÿ��DMA��ֻ�����ᵽ�̶����ڴ���*/ 
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  /*�趨�������ݿ�ȣ�������DMAҪȡ�����Ĵ�С*/  
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  /*�趨�ڴ�ĵĿ��*/  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 	/*�趨DMA������ѭ������ģʽ��������DMAҪ��ͣ�İ��ˣ�����͵��*/    
 DMA_InitStructure.DMA_Priority = DMA_Priority_High;   /*�趨DMAѡ����ͨ��������ȼ�*/
 DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	
 DMA_Init(DMA1_Channel1, &DMA_InitStructure);  
 /* Enable DMA channel1��CPU�кü���DMA���飬����ֻ�� DMA1_Channel1�������*/   
 DMA_Cmd(DMA1_Channel1, ENABLE);   
}
	
/*
	DMA_InitTypeDef DMA_InitStructure; 
DMA_DeInit(DMA1_Channel1); //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ 
DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //DMA����ADC����ַ 
DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value; //DMA�ڴ����ַ 
DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //�ڴ���Ϊ���ݴ����Ŀ�ĵ� 
DMA_InitStructure.DMA_BufferSize = N*M; //DMAͨ����DMA����Ĵ�С 
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ������� 
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�Ĵ������� 
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //���ݿ��Ϊ16λ 
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ 
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //������ѭ������ģʽ 
DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�и����ȼ� 
DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫�� 
DMA_Init(DMA1_Channel1, &DMA_InitStructure); //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ�� */

	//------------------------------------------------------------------
//��������void DAC_Configuration()
//���������null
//���ز�����null
//˵��:ad��ʼ������
//------------------------------------------------------------------
void DAC_Configuration(void)
{
DAC_InitTypeDef DAC_InitType;
DAC_InitType.DAC_Trigger=DAC_Trigger_None;//��ʹ�ô������� TEN1=0
DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;//DAC1�������ر� BOFF1=1
DAC_Init(DAC_Channel_1,&DAC_InitType);//��ʼ��DACͨ��1
DAC_Cmd(DAC_Channel_1, ENABLE);//ʹ��DAC1
DAC_SetChannel1Data(DAC_Align_12b_R, 0);//12λ�Ҷ������ݸ�ʽ����DACֵ
}
///////////////////////////////////////////////////////////
/**
* ��ʼ���������Ź�
* prer:��Ƶ��:0~7(ֻ�е� 3 λ��Ч!)
* ��Ƶ����=4*2^prer.�����ֵֻ���� 256!
* rlr:��װ�ؼĴ���ֵ:�� 11 λ��Ч.
* ʱ�����(���):Tout=((4*2^prer)*rlr)/40 (ms).
*/
void IWDG_Init(void)
{
IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); /* ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����*/
IWDG_SetPrescaler(IWDG_Prescaler_16);/*����IWDGԤ��Ƶֵ:����IWDGԤ��Ƶֵ*/
IWDG_SetReload(349); /*����IWDG��װ��ֵ*/
IWDG_ReloadCounter();/*����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������*/
IWDG_Enable();/*ʹ��IWDG*/
}
//////////////////////////////////////////////////////////
//ι�������Ź�
void IWDG_Feed(void)
{
IWDG_ReloadCounter();/*reload*/
} 
