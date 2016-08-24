#ifndef CONFIG_SOFTWARE_H
#define CONFIG_SOFTWARE_H






/**
 *@brief gprs �����ò���. 
 *
 *@detail Э��ţ��绰���룬ip��ַ�������С�����á� 
 */
typedef struct 
{
    char serialnum[16];          ///<	ϵ�к�
    char protocoltype[16];       ///<��Э���
    char ipaddr[16];             ///<	IP��ַ
    char portnum[16];            ///<	
    char telnum[16];             ///<	�绰����
    int bufsize;            	///<	�����С

}ConfGprs;

/** ���õ�Ԫ�Ĺܲ���Ҫʵ�ֵĸ��½ӿ�
 * �����÷����仯ʱ����.
 *
 */
typedef void (*confUpdate)(void);



extern ConfGprs g_config_data;

void set_default_config_data(void);
#endif