/**
* @file 		config_software.c
* @brief		ϵͳ��������ֵ��������ݺ����÷���.
* @details		��Ϊ���⣬�ṩע���ɾ���۲��ߵķ�������������Ϣ���ͱ仯ʱ��֪ͨ�۲���.
* @author		sundh
* @date			16-08-24
* @version		V001
* @par Copyright (c): 
* 		XXX??
* @par History:         
*	version: author, date, desc\n
*	V001:sundh,16-0824,����
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
 * @brief ����ϵͳģ���Ĭ�ϲ���.
 *
 * @details ������gprs��Ĭ�ϲ���.
 * 
 * @param[in]	void.
 * @param[out]	
 * @retval	void.
 * @par ��ʶ��
 * 		����
 * @par ����
 * 		��
 * @par �޸���־
 * 		sundh��2016-08-24����
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
 * @brief ʵ����ϵͳ�����õ�Ԫ.
 *
 * @details �������ڱ���۲��ߵ�����.
 * 
 * @param[in]	void.
 * @retval	void.
 * @par ��ʶ��
 * 		����
 * @par ����
 * 		��
 * @par �޸���־
 * 		sundh��2016-08-24����
 */
void	init_confSoftware(void)
{
	list_init( &ObserverList, free);
}

/**
 * @brief ע�����ñ仯����Ĺ۲���.
 *
 * @details This is a detail description.
 * 
 * @param[in]	inArgName input argument description.
 * @param[out]	outArgName output argument description. 
 * @retval	OK	�ɹ�
 * @retval	ERROR	���� 
 * @par ��ʶ��
 * 		����
 * @par ����
 * 		��
 * @par �޸���־
 * 		sundh��2016-08-24����
 */
void registerConfChgObserver(confUpdate *update)
{
	
}
