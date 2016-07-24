/*gprs 的tcp模块
	* 提供tcp操作接口
	*
	
	
	*/
#include "module_tcp.h"

static err_t gprs_tcp_init( void *t)
{
	
	return ERR_OK;
}
static err_t gprs_tcp_destory( void *t)
{
	
	return ERR_OK;
}

static err_t gprs_connect( void *t, void *target)
{
	
	return ERR_OK;
}

static err_t gprs_disconnect( void *t, int socketnum)
{
	
	return ERR_OK;
}

static err_t gprs_send_tcp_data( void *t, int socketnum, void *sendbuf, int sendsize)
{
	
	return ERR_OK;
}

CTOR(gprs_tcp_operate)
FUNCTION_SETTING(init, gprs_tcp_init);
FUNCTION_SETTING(destory, gprs_tcp_destory);
FUNCTION_SETTING(connect_tcp_server, gprs_connect);
FUNCTION_SETTING(dis_connect_tcp_S, gprs_disconnect);
FUNCTION_SETTING(send_tcp_data, gprs_send_tcp_data);
END_CTOR



