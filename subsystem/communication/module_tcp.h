#ifndef __MODULE_TCP_H
#define __MODULE_TCP_H
#include "err_head.h"
#include "lw_oopc.h"


CLASS( gprs_tcp_operate) 
{
	err_t ( *init)( void *);
	err_t ( *destory)( void *);
	err_t ( *connect_tcp_server)( void *, void *);
	err_t ( *dis_connect_tcp_S)(void *, int);
	err_t ( *send_tcp_data)( void *, int , void *, int);
	err_t ( *input_tcp_data)( void *, void *, int);
	
	
	
	
};




#endif
