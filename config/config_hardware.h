#ifndef CONFIG_HARDWARE_H
#define CONFIG_HARDWARE_H
#include "stm32f10x_usart.h"
#define GPRS_UART		USART3		///< gprsģ��ʹ�õĴ��ں�	
/**
 *@brief gprs �����ò���. 
 *
 *@detail Э��ţ��绰���룬ip��ַ�������С�����á� 
 */
typedef struct 
{
    char serialnum[16];          ///<	ϵ�к�
    char protocoltype[16];       ///<��Э���
    char ipaddr[16];             ///<	IP��ַ
    char portnum[16];            ///<	
    char telnum[16];             ///<	�绰����
    int bufsize;            						///<	�����С

}ConfGprs;

extern USART_InitTypeDef USART_InitStructure;
extern USART_InitTypeDef Conf_GprsUsart;
extern ConfGprs g_config_data;
#endif

