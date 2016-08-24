/**
  ******************************************************************************
  * @file    config_hardware.c
  * @author  sundh
  * @version V0.1.1
  * @date    2016-7-30
  * @brief   系统外设的配置的默认值
  * 
  *        
  ******************************************************************************
  * @attention
  *
  *
  * <h2><center>&copy;   </center></h2>
  ******************************************************************************
	---------------------------------------------------------------------------- 

	  Change History :                                                           

	  <Date>      <Version>  <Author>       | <Description>                    

	---------------------------------------------------------------------------- 

	  2016/07/30 | 0.1.1   	| sundh     		| Create file                      

	---------------------------------------------------------------------------- 

  */
#include "config_hardware.h"

USART_InitTypeDef USART_InitStructure = {
		9600,
		USART_WordLength_8b,
		USART_StopBits_1,
		USART_Parity_No,
		USART_Mode_Rx | USART_Mode_Tx,
		USART_HardwareFlowControl_None,
};
USART_InitTypeDef Conf_GprsUsart = {
		9600,
		USART_WordLength_8b,
		USART_StopBits_1,
		USART_Parity_No,
		USART_Mode_Rx | USART_Mode_Tx,
		USART_HardwareFlowControl_None,
		
	
};





