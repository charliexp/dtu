#include "times.h"
#include "stm32f10x_tim.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cmsis_os.h"
TIME2_T g_time2;

void Delay(unsigned long  nCount)
{
    for(; nCount != 0; nCount--);
}

void delay_GSM(unsigned int i)          //延时函数
{
    unsigned int i_delay,j_delay;
    for(i_delay=0;i_delay<i;i_delay++)
    {for(j_delay=0;j_delay<3000;j_delay++)
        {;}}
//			int delay_ms = i / 5;
//			if (delay_ms == 0)	delay_ms = 1;
//			osDelay(delay_ms);
}

void delay_xms(unsigned int i)
{
    unsigned int i_delay,j_delay;
    for(i_delay=0;i_delay<i;i_delay++)
    {for(j_delay=0;j_delay<1000;j_delay++)
        {;}}
}

void TIM2_IRQHandler(void)          //定时器中断约10ms
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {     
        g_time2.time_overflow_100ms++;		   //100ms
		g_time2.time_overflow_1s++;			   //1S

        if (g_time2.time_overflow_100ms == 10)  //100ms 
        {
                g_time2.flag = 1;
                g_time2.time_overflow_100ms = 0;
        }

        if(g_time2.time_overflow_1s == 250)   //1s GPRS send infomation
        {

            g_time2.send_gprs_position ++;
            g_time2.time_overflow_1s = 0;
        }

        TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }

//    if(is_config_analysising())                 //得到配置数据
//    {
//		PUT(buf_uart1.buf);
//		if(parser_config_data(buf_uart1.buf))							//解析得到配置数据
//		{
//			PUT("\r\nerror config data!\r\n");
//			clear_buf_uart1();
//        	clean_config_flag();
//			return ; //如果不是正确的数据	就反馈
//		}

//        write_data_eeprom(buf_uart1.buf);
//        clear_buf_uart1();
//        clean_config_flag();

//        PUT("\r\nOK\r\n");
//		
//        PUT("read eeprom:");
//        PUT(read_data_eeprom());
//        PUT("\r\n\r\n");
//        return ;
//    }
}

void clean_time2_flags(void)
{
    g_time2.flag = 0;
    g_time2.time_overflow_1s = 0;
    g_time2.time_overflow_100ms = 0;
    g_time2.send_gprs_position = 0;
}



unsigned char is_enable_send_gprs_position(void)     //允许发送GPRS数据
{
    if(g_time2.send_gprs_position >= 5)          //5s
    {
        g_time2.send_gprs_position = 0;

        return 1 ;
    }
    return 0 ;
}

