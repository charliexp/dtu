#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include "lw_oopc.h"
#include "subsys_commu.h"
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
 SubS_comm	*Obj_Cmm;			//通讯子系统对象，在系统中处理一切与数据透传相关业务
 
 
 
void CMM_Thread (void const *argument);                             // thread function
osThreadId tid_CMM_Thread;                                          // thread id
osThreadDef (CMM_Thread, osPriorityNormal, 1, 0);                   // thread object

int Init_CMM_Thread (void) {
	
	err_t ret = 0;

  tid_CMM_Thread = osThreadCreate (osThread(CMM_Thread), NULL);
  if (!tid_CMM_Thread) return(-1);
  
//通讯子系统初始化
	Obj_Cmm = SubS_comm_new();
	if( Obj_Cmm->init( Obj_Cmm))
	{
		return(-1);
	}
	
  return(0);
}

void CMM_Thread (void const *argument) {

  while (1) {
    ; // Insert thread code here...
    osThreadYield ();                                           // suspend thread
  }
}

static err_t cmm_init(void *t)
{
	SubS_comm *cthis = ( SubS_comm*)t;
	cthis->tcp_opr = gprs_tcp_operate_new();
	if( cthis->tcp_opr == NULL)
		return ERR_MEM_UNAVAILABLE;
			
	if( cthis->tcp_opr->init( cthis->tcp_opr) < 0)
		return ERR_UNKOWN;
	
	return ERR_OK;
}

static err_t cmm_destory(void *t)
{
	SubS_comm *cthis = ( SubS_comm*)t;
	
	if( cthis->tcp_opr->destory( cthis->tcp_opr) < 0)
		return ERR_UNKOWN;
	
	return ERR_OK;
}



CTOR(SubS_comm)
FUNCTION_SETTING(init, cmm_init);
FUNCTION_SETTING(destory, cmm_destory);

END_CTOR




