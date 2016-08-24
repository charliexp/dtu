#ifndef CONFIG_HARDWARE_H
#define CONFIG_HARDWARE_H
#include "stm32f10x_usart.h"


#define	GPRS_COM			3			///< gprsģ��ʹ�õĴ��ں�	
#define	DEBUG_COM			1

#if GPRS_COM == 3
#define GPRS_USART	USART3
#elif GPRS_COM == 1
#define GPRS_USART	USART1
#endif

#if DEBUG_COM == 3
#define DEBUG_USART	USART3
#elif DEBUG_COM == 1
#define DEBUG_USART	USART1
#endif



extern USART_InitTypeDef USART_InitStructure;
extern USART_InitTypeDef Conf_GprsUsart;




#endif

