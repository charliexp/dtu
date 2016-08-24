#ifndef __SUBSYS_COMMU_H
#define __SUBSYS_COMMU_H
#include "lw_oopc.h"
#include "err_head.h"
#include "module_tcp.h"


CLASS(SubS_comm) 
{
	err_t (*init)(void *);
	err_t (*destory)(void *);
	

	
	// todo:	后续添加短信操作
	
	
	
	//todo:	后继添加串口通讯操作接口
	
	
};



int Init_CMM_Thread (void);

#endif

