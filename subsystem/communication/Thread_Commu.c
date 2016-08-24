#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include "subsys_commu.h"
#include "gprs_uart.h"
#include "gprs.h"
#include "stdio.h"
#include "times.h"
#include <string.h>
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
 SubS_comm	*Obj_Cmm;			//通讯子系统对象，在系统中处理一切与数据透传相关业务
 
 
 
void CMM_Thread (void const *argument);                             // thread function
osThreadId tid_CMM_Thread;                                          // thread id
osThreadDef (CMM_Thread, osPriorityNormal, 1, 0);                   // thread object

int Init_CMM_Thread (void) {
 
  
//通讯子系统初始化
	Obj_Cmm = SubS_comm_new();
	if( Obj_Cmm->init( Obj_Cmm))
	{
		return(-1);
	}
	
	tid_CMM_Thread = osThreadCreate (osThread(CMM_Thread), NULL);
  if (!tid_CMM_Thread) return(-1);
	
  return(0);
}

int  icount = 0;		  //心跳数
char wendu_gprs[BUFLEN];  //发送到服务器的温度

void CMM_Thread (void const *argument) {
	char *val = NULL ;		/* 反馈结果	*/
  while (1) {
	val = NULL;
	if(	g_gprs_conn_ok )
	{

		val =  strstr((const char*)buf_uart3.buf,"CLOSED");		//??????????
		if(val)
		{
			g_gprs_conn_ok = 0;
			clear_buf_uart1();
			val = NULL;
		}
		val =  strstr((const char*)buf_uart3.buf,"SEND FAIL");	//???????
		if(val)
		{
			clear_buf_uart1();
			g_gprs_conn_ok = 0;
			val = NULL;
		}

		val =  strstr((const char*)buf_uart3.buf,"ERROR");	//???????
		if(val)
		{
			clear_buf_uart1();
			g_gprs_conn_ok = 0;
			val = NULL;
		}

		if(strlen(buf_uart1.buf)>0&&!ibusy)					 //????1???
		{									 
			send_gprs_data(buf_uart1.buf,1);		 //??GPRS??
			clear_buf_uart1();
		}

		if(strlen(buf_uart3.buf)>0)					 //????3??? ,???GPRS???????uart3?
		{	
			clear_buf_uart3();
		}

		if(is_enable_send_gprs_position()&&!ibusy)				 //????????
		{	
			icount++;
			gprs_heart(wendu_gprs,icount);						 
			printf("send beat %d \r\n", icount);
			
			if(icount > 32000)
				icount = 0;
		}
	}			//if(	g_gprs_conn_ok )
	if(!g_gprs_conn_ok)									 
	{	
		current_status = GPRS_OPEN_FINISH;
		creat_tcp();
	}
  }		//while(1)
}

static err_t cmm_init(void *t)
{
	SubS_comm *cthis = ( SubS_comm*)t;
	
	start_gprs_mode();	
	init_gprs();
	
	
	if(is_gprs_mode_status_ok())
	{
			PUT("GSM OK\r\n");
	}
	else
	{
			PUT("GSM NO\r\n");
	}
	
	open_gprs_simple();	
	PUT("open tcp/udp finished \r\n");
	creat_tcp();									  //创建gprs通信
	PUT("connect to server finished \r\n");

	if (current_status == TCP_IP_OK)
	{
			PUT("conn ok \r\n");
	}
	else
	{
			PUT("conn error \r\n");
	}

	clean_time2_flags();
	send_gprs_data("csic.taobao.com",1);		 //??GPRS??
	
	
	
	return ERR_OK;
}

static err_t cmm_destory(void *t)
{
	SubS_comm *cthis = ( SubS_comm*)t;
	

	
	return ERR_OK;
}



CTOR(SubS_comm)
FUNCTION_SETTING(init, cmm_init);
FUNCTION_SETTING(destory, cmm_destory);

END_CTOR




