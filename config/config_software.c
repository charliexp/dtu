/**
* @file 		config_software.c
* @brief		系统的软件部分的配置数据和配置方法.
* @details		作为主题，提供注册和删除观察者的方法。当配置信息发送变化时，通知观察者.
* @author		sundh
* @date			16-08-24
* @version		V001
* @par Copyright (c): 
* 		XXX??
* @par History:         
*	version: author, date, desc\n
*	V001:sundh,16-0824,创建
*/
#include "config_software.h"
#include "stdio.h"
#include "string.h"
#include "gprs.h"
#include "list.h"
#include "err_head.h"


static List	ObserverList;
ConfGprs g_config_data ;


/**
 * @brief 设置系统模块的默认参数.
 *
 * @details 设置了gprs的默认参数.
 * 
 * @param[in]	void.
 * @param[out]	
 * @retval	void.
 * @par 标识符
 * 		保留
 * @par 其它
 * 		无
 * @par 修改日志
 * 		sundh于2016-08-24创建
 */
void set_default_config_data(void)
{
    sprintf(g_config_data.serialnum,"%s",SERNUM);
    sprintf(g_config_data.protocoltype,"%s",PROTOTOCOL);
    sprintf(g_config_data.ipaddr,"%s",IPADDR);
    sprintf(g_config_data.portnum,"%s",PORTNUM);
    sprintf(g_config_data.telnum,"%s",TELNUM);
    g_config_data.bufsize = CACHESIZE;
}

/**
 * @brief 实例化系统的配置单元.
 *
 * @details 创建用于保存观察者的链表.
 * 
 * @param[in]	void.
 * @retval	void.
 * @par 标识符
 * 		保留
 * @par 其它
 * 		无
 * @par 修改日志
 * 		sundh于2016-08-24创建
 */
void	init_confSoftware(void)
{
	list_init( &ObserverList, free);
}

/**
 * @brief 注册配置变化主题的观察者.
 *
 * @details This is a detail description.
 * 
 * @param[in]	inArgName input argument description.
 * @param[out]	outArgName output argument description. 
 * @retval	OK	成功
 * @retval	ERROR	错误 
 * @par 标识符
 * 		保留
 * @par 其它
 * 		无
 * @par 修改日志
 * 		sundh于2016-08-24创建
 */
void registerConfChgObserver(confUpdate *update)
{
	
}
