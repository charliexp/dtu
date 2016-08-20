#ifndef CONFIG_HARDWARE_H
#define CONFIG_HARDWARE_H
#include "stm32f10x_usart.h"
#define GPRS_UART		USART3		///< gprs模块使用的串口号	
/**
 *@brief gprs 的配置参数. 
 *
 *@detail 协议号，电话号码，ip地址，缓存大小的配置。 
 */
typedef struct 
{
    char serialnum[16];          ///<	系列号
    char protocoltype[16];       ///<　协议号
    char ipaddr[16];             ///<	IP地址
    char portnum[16];            ///<	
    char telnum[16];             ///<	电话号码
    int bufsize;            						///<	缓存大小

}ConfGprs;

extern USART_InitTypeDef USART_InitStructure;
extern USART_InitTypeDef Conf_GprsUsart;
extern ConfGprs g_config_data;
#endif

