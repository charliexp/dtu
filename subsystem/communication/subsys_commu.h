#ifndef __SUBSYS_COMMU_H
#define __SUBSYS_COMMU_H
#include "lw_oopc.h"
#include "err_head.h"
#include "module_tcp.h"


CLASS(SubS_comm) 
{
	err_t (*init)(void *);
	err_t (*destory)(void *);
	

	
	// todo:	������Ӷ��Ų���
	
	
	
	//todo:	�����Ӵ���ͨѶ�����ӿ�
	
	
};



int Init_CMM_Thread (void);

#endif

