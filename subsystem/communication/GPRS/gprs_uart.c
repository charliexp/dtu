/**
  ******************************************************************************
  * @file    gprs_uart.c
  * @author  sundh
  * @version V0.1.1
  * @date    2016-7-30
  * @brief   为gprs模块的uart通讯提供接口.
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
#include "gprs_uart.h"

#include "err_head.h"

UART_BUF buf_uart1;     //pc
UART_BUF buf_uart2;     //485
UART_BUF buf_uart3;     //gprs
TP_BUF buf_tp;          //tp



void debug_put_word(unsigned char word)
{
    send_data_uart1('[');
    send_data_uart1(word);
    send_data_uart1(']');

}
void clear_buf_uart1(void)
{
    unsigned int i = 0 ,c ;
    c = BUFLEN +1 ;
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);

    for( i = 0 ; i < c ; i ++)
    {
        buf_uart1.buf[i] = 0x0 ;
    }

    buf_uart1.index = 0 ;

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
void clear_buf_uart2(void)
{
    unsigned int i = 0 ,c ;
    c = BUFLEN +1 ;
    USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);

    for( i = 0 ; i < c ; i ++)
    {
        buf_uart2.buf[i] = 0x0 ;
    }

    buf_uart2.index = 0 ;

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

void clear_buf_uart3(void)
{
    unsigned int i = 0 ,c ;
    c = BUFLEN +1 ;
    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);

    for( i = 0 ; i < c ; i ++)
    {
        buf_uart3.buf[i] = 0x0 ;
    }

    buf_uart3.index = 0 ;

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}

void send_data_uart1(unsigned char Data)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, Data);
}

void send_data_uart2(unsigned char Data)
{
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    USART_SendData(USART2, Data);
}

void send_data_uart3(unsigned char Data)
{
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    USART_SendData(USART3, Data);
}

void send_string_uart1(char * S)
{
    while(*S)
    {
        send_data_uart1(*S++);
    }

}

void send_string_uart2(char * S)
{
    while(*S)
    {
        send_data_uart2(*S++);
    }
}
void send_string_uart3(char * S)
{
    while(*S)
    {
        send_data_uart3(*S++);
    }
}

void uart_data_send(unsigned char Data)
{
    while(USART_GetFlagStatus( GPRS_USART, USART_FLAG_TXE) == RESET);
    USART_SendData( GPRS_USART, Data);
}

void uart_string_send(char * S)
{
    while(*S)
    {
        uart_data_send(*S++);
    }

}


void gprs_receive_process_event(unsigned char ch )
{
    if(buf_uart3.index >= BUFLEN)
    {
        buf_uart3.index = 0 ;
    }
    else
    {
        buf_uart3.buf[buf_uart3.index++] = ch;
    }
}


void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE)==SET)
    {
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);
    }

    //??-??????????SR,??DR???????????????[??????]
    if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART2,USART_FLAG_ORE);
    }
}

#if GPRS_COM == 3
void USART3_IRQHandler(void)
#elif	GPRS_COM == 1
void USART1_IRQHandler(void)
#endif
{
    if(USART_GetITStatus( GPRS_USART, USART_IT_RXNE) == SET)
    {
        gprs_receive_process_event(USART_ReceiveData( GPRS_USART));
        USART_ClearITPendingBit( GPRS_USART,USART_IT_RXNE);
    }

    //溢出，如果发生溢出需要先读SR,再读DR寄存器可清除不再进入中断的问题
    if(USART_GetFlagStatus( GPRS_USART,USART_FLAG_ORE) == SET)
    {
        gprs_receive_process_event(USART_ReceiveData( GPRS_USART));
        USART_ClearFlag( GPRS_USART,USART_FLAG_ORE);
    }
}

