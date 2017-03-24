#include "stm32f10x.h"
/*定义ADC1_DR_Address  为((u32)0x40012400+0x4c) ，因为存放AD转换结果的寄存器的地址就是0x4001244c*/ 
#define  ADC1_DR_Address    ((u32)0x40012400+0x4c)  
///*定义变量ADC_ConvertedValue,放AD1通道10转换的数据*/
//__IO uint16_t ADC_ConvertedValue;
#define N 10 //每通道采50次
#define M 8 //为8个通道
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
  ErrorStatus HSEStartUpStatus;      //枚举变量，定义高速时钟的启动状态
  RCC_DeInit();                   //RCC系统重置，用于Debug目的
  RCC_HSEConfig(RCC_HSE_ON);                 //使能高速时钟源HSE  
  HSEStartUpStatus = RCC_WaitForHSEStartUp();    //等待HSE稳定
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
   	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_DAC|RCC_APB1Periph_USART3, ENABLE);	//使能USART1,2，GPIOA时钟
	  RCC_ADCCLKConfig(RCC_PCLK2_Div8); //72M/8=9
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //enable DMA request
}
//------------------------------------------------------------------
//函数名：void GPIO_Configuration()
//输入参数：null
//返回参数：null
//说明：GPIO初始化函数
//------------------------------------------------------------------
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //GPIO初始化结构体声明
	//////////////////////////////////////////////////////////////////////////////////////重映射
//	GPIO_AFIODeInit();
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	///////////////////////////////////////////////////////////////////////////////////////串口通信1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;          //TX1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);      //A端口
	
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;          //RX1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //浮空输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOA, &GPIO_InitStructure);      //A端口
	
///////////////////////////////////////////////////////////////////////////////串口通信	USART2
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;          //TX2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);      //A端口
	
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;          //RX2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //浮空输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOA, &GPIO_InitStructure);      //A端口
///////////////////////////////////////////////////////////////////////////////////////串口通信3
		  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;          //TX3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);      //A端口
	
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;          //RX3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //浮空输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOB, &GPIO_InitStructure);      //A端口
////////////////////////////////////////////////////////////////////////////////////////GPIO口的设置————模拟输入
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;    //模拟输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOA, &GPIO_InitStructure);      //A端口
		
  	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;    //模拟输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOB, &GPIO_InitStructure);      //B端口
	////////////////////////////////////////////////////////////////////////////////////////GPIO口的设置————数字输入
//	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;         
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //数字输入
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
//	  GPIO_Init(GPIOA, &GPIO_InitStructure);      //A端口
		
  	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //数字输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOD, &GPIO_InitStructure);      //D端口	
			////////////////////////////////////////////////////////////////////////////////////////GPIO口的设置————数字输出
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12;         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;    //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOC, &GPIO_InitStructure);      //C端口
		
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;    //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOB, &GPIO_InitStructure);      //C端口
////////////////////////////////////////////////////////////////////////////////////////GPIO口的设置————DAC输出
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14;         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	  GPIO_Init(GPIOB, &GPIO_InitStructure);      //A端口

}
//------------------------------------------------------------------
//函数名：void NVIC_Configuration()
//返回参数：null
//说明：NVIC初始化函数
//输入参数：null
//------------------------------------------------------------------
void NVIC_Configuration(void)
{              
  NVIC_InitTypeDef NVIC_InitStructure;       //NVIC初始化结构体声明

//////////////////////////////////////////////串口中断配置
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;         //设置串口2中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级 0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    //子优先级为0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //使能
  NVIC_Init(&NVIC_InitStructure);	
//////////////////////////////////////////////串口中断配置
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;         //设置串口3中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级 0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =2 ;    //子优先级为0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //使能
  NVIC_Init(&NVIC_InitStructure);	
	//////////////////////////////////////////////串口中断配置
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;         //设置串口1中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级 0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =0 ;    //子优先级为0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //使能
  NVIC_Init(&NVIC_InitStructure);	
/////////////////////////////////////////////////////定时器中断配置
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;           //设置定时器4全局中断
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;        //抢占优先级 1
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            //子优先级为0
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能
//  NVIC_Init(&NVIC_InitStructure);
//	///////////////////////////////////////////////////定时器中断配置
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;           //设置定时器5全局中断
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;        //抢占优先级 1
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            //子优先级为0
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能
//  NVIC_Init(&NVIC_InitStructure);
}
//------------------------------------------------------------------
//函数名：void USART_Configuration()
//输入参数：null
//返回参数：null
//说明:串口初始化函数
//------------------------------------------------------------------
void USART_Configuration(void)
	{
  USART_InitTypeDef USART_InitStructure;                   //串口初始化结构体声明
  USART_ClockInitTypeDef USART_ClockInitStruct;
  USART_InitStructure.USART_BaudRate = 9600;      //设置波特率为115200bps
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //数据位8位
  USART_InitStructure.USART_StopBits = USART_StopBits_1;   //停止位1位
  USART_InitStructure.USART_Parity = USART_Parity_No;    //无校验位
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件流控
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;     //接受和发送模式都打开
		
  USART_ClockInitStruct.USART_Clock=USART_Clock_Disable;      //串口时钟禁止
  USART_ClockInitStruct.USART_CPOL=USART_CPOL_Low;        //数据低电平有效
  USART_ClockInitStruct.USART_CPHA=USART_CPHA_2Edge;    //配置CPHA使数据在第2个边沿的时候被捕获
  USART_ClockInitStruct.USART_LastBit=USART_LastBit_Disable;  // 禁用最后一位,使对应的时钟脉冲不会再输出到SCLK引脚
		
 USART_ClockInit(USART1, &USART_ClockInitStruct);      //配置USART与时钟相关的设置
  USART_Init(USART1, &USART_InitStructure);       //配置串口参数函数
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);       //使能接收中断
//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);    //使能发送缓冲空中断
//USART_ITConfig(USART1, USART_IT_TC, ENABLE);    //使能发送完成中断
  USART_ClearFlag(USART1,USART_FLAG_TC);         //清除发送完成标志位
  USART_Cmd(USART1, ENABLE); 
	
  USART_ClockInit(USART2, &USART_ClockInitStruct);      //配置USART与时钟相关的设置
  USART_Init(USART2, &USART_InitStructure);       //配置串口参数函数
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);       //使能接收中断
//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);    //使能发送缓冲空中断
//USART_ITConfig(USART1, USART_IT_TC, ENABLE);    //使能发送完成中断
  USART_ClearFlag(USART2,USART_FLAG_TC);         //清除发送完成标志位
  USART_Cmd(USART2, ENABLE);         //使能串口2
		
	USART_ClockInit(USART3, &USART_ClockInitStruct);      //配置USART与时钟相关的设置
  USART_Init(USART3, &USART_InitStructure);       //配置串口参数函数
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);       //使能接收中断
//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);    //使能发送缓冲空中断
//USART_ITConfig(USART1, USART_IT_TC, ENABLE);    //使能发送完成中断
  USART_ClearFlag(USART3,USART_FLAG_TC);         //清除发送完成标志位
  USART_Cmd(USART3, ENABLE);         //使能串口3
}
	//------------------------------------------------------------------
//函数名：void AD_Configuration()
//输入参数：null
//返回参数：null
//说明:ad初始化函数
//------------------------------------------------------------------
void ADC_Configuration(void)
{
ADC_InitTypeDef ADC_InitStructure;
ADC_DeInit(ADC1);//将外设ADC1的全部寄存器重设为缺省值
ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;//ADC工作模式:ADC1和ADC2工作在独立模式
ADC_InitStructure.ADC_ScanConvMode=ENABLE;//模数转换工作在扫描模式
ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;//模数转换工作在连续转换模式
ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//外部触发转换关闭
ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//ADC数据右对齐
ADC_InitStructure.ADC_NbrOfChannel=M;//顺序进行规则转换的ADC通道的数目
ADC_Init(ADC1,&ADC_InitStructure);
//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器
//设置指定ADC的规则组通道，设置它们的转化顺序和采样时间 //ADC1,ADC通道x,规则采样顺序值为y,采样时间为239.5周期 
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
ADC_DMACmd(ADC1, ENABLE);   // 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）
ADC_Cmd(ADC1, ENABLE); //使能指定的ADC1  
ADC_ResetCalibration(ADC1); //复位指定的ADC1的校准寄存器
while(ADC_GetResetCalibrationStatus(ADC1)); //获取ADC1复位校准寄存器的状态,设置状态则等待   
ADC_StartCalibration(ADC1); //开始指定ADC1的校准状态  
while(ADC_GetCalibrationStatus(ADC1)); //获取指定ADC1的校准程序,设置状态则等待 
}
	//------------------------------------------------------------------
//函数名：void DMA_Configuration()
//输入参数：null
//返回参数：null
//说明:ad初始化函数
//------------------------------------------------------------------
void DMA_Configuration(void)
{
	DMA_InitTypeDef  DMA_InitStructure; 
	DMA_DeInit(DMA1_Channel1);  /* 将与DMA有关的寄存器设我初始值 */  
	DMA_InitStructure.DMA_PeripheralBaseAddr =ADC1_DR_Address ;   /*定义DMA外设基地址, 这里的ADC1_DR_Address 是用户自己定义的，即为存放转换结果的寄存器 ，他的作用就是告诉DMA取数就到ADC1_DR_Address 这里来取。*/ 
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32)&AD_ReadValue;  /*定义内存基地址，即告诉DMA要将从AD中取来的数放到ADC_Value中 */  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;    /*定义AD外设作为数据传输的来源，即告诉DMA是将AD中的数据取出放到内存中，不能反过来*/  
  DMA_InitStructure.DMA_BufferSize = M*N;   /*指定DMA通道的DMA缓存的大小,即告诉DMA开辟几个内存空间*/ 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   /*设定寄存器地址固定，即告诉DMA，只从固定的一个地方取数*/  
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;     /*设定内存地址固定，即每次DMA，只将数搬到固定的内存中*/ 
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  /*设定外设数据宽度，即告诉DMA要取的数的大小*/  
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  /*设定内存的的宽度*/  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 	/*设定DMA工作再循环缓存模式，即告诉DMA要不停的搬运，不能偷懒*/    
 DMA_InitStructure.DMA_Priority = DMA_Priority_High;   /*设定DMA选定的通道软件优先级*/
 DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA通道x没有设置为内存到内存传输
	
 DMA_Init(DMA1_Channel1, &DMA_InitStructure);  
 /* Enable DMA channel1，CPU有好几个DMA秘书，现在只用 DMA1_Channel1这个秘书*/   
 DMA_Cmd(DMA1_Channel1, ENABLE);   
}
	
/*
	DMA_InitTypeDef DMA_InitStructure; 
DMA_DeInit(DMA1_Channel1); //将DMA的通道1寄存器重设为缺省值 
DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //DMA外设ADC基地址 
DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value; //DMA内存基地址 
DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //内存作为数据传输的目的地 
DMA_InitStructure.DMA_BufferSize = N*M; //DMA通道的DMA缓存的大小 
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变 
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增 
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位 
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位 
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //工作在循环缓存模式 
DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有高优先级 
DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA通道x没有设置为内存到内存传输 
DMA_Init(DMA1_Channel1, &DMA_InitStructure); //根据DMA_InitStruct中指定的参数初始化DMA的通道 */

	//------------------------------------------------------------------
//函数名：void DAC_Configuration()
//输入参数：null
//返回参数：null
//说明:ad初始化函数
//------------------------------------------------------------------
void DAC_Configuration(void)
{
DAC_InitTypeDef DAC_InitType;
DAC_InitType.DAC_Trigger=DAC_Trigger_None;//不使用触发功能 TEN1=0
DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;//DAC1输出缓存关闭 BOFF1=1
DAC_Init(DAC_Channel_1,&DAC_InitType);//初始化DAC通道1
DAC_Cmd(DAC_Channel_1, ENABLE);//使能DAC1
DAC_SetChannel1Data(DAC_Align_12b_R, 0);//12位右对齐数据格式设置DAC值
}
///////////////////////////////////////////////////////////
/**
* 初始化独立看门狗
* prer:分频数:0~7(只有低 3 位有效!)
* 分频因子=4*2^prer.但最大值只能是 256!
* rlr:重装载寄存器值:低 11 位有效.
* 时间计算(大概):Tout=((4*2^prer)*rlr)/40 (ms).
*/
void IWDG_Init(void)
{
IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); /* 使能对寄存器IWDG_PR和IWDG_RLR的写操作*/
IWDG_SetPrescaler(IWDG_Prescaler_16);/*设置IWDG预分频值:设置IWDG预分频值*/
IWDG_SetReload(349); /*设置IWDG重装载值*/
IWDG_ReloadCounter();/*按照IWDG重装载寄存器的值重装载IWDG计数器*/
IWDG_Enable();/*使能IWDG*/
}
//////////////////////////////////////////////////////////
//喂独立看门狗
void IWDG_Feed(void)
{
IWDG_ReloadCounter();/*reload*/
} 
