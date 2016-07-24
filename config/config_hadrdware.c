/* 硬件配置数据结构   */



#include "config_hardware.h"


USART_InitTypeDef Conf_Usrt3 = {
		15200,
		USART_WordLength_8b,
		USART_StopBits_1,
		USART_Parity_No,
		USART_Mode_Rx | USART_Mode_Tx,
		USART_HardwareFlowControl_None,
		
	
};
