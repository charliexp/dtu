#ifndef __GPRS_UART_H
#define __GPRS_UART_H
#include "stm32f10x_usart.h"
#include "gprs.h"


#define BUFLEN 81
//#define PUT_2 send_string_uart2
#define PUT_2 send_string_uart1
#define PUT send_string_uart1


typedef struct _TP_BUF
{
    char buf[CACHESIZE];                // 
    unsigned int index ;
}TP_BUF;
typedef struct _UART_BUF
{
    char buf [BUFLEN+1];                // ??????????????????'0'
    unsigned int index ;
}UART_BUF;


///< gprs 的串口字符串发送
void uart_string_send(char * S);
///< gprs 向串口发送一个字节
void uart_data_send(unsigned char Data);
void send_data_uart1(unsigned char Data);
void send_string_uart1(char * S);
void send_string_uart2(char * S);
void clear_buf_uart3(void);
void debug_put_word(unsigned char word);
void clear_buf_uart2(void);



extern UART_BUF buf_uart1;
extern UART_BUF buf_uart2;
extern UART_BUF buf_uart3;
extern TP_BUF buf_tp;

#endif
