#ifndef CONFIG_SOFTWARE_H
#define CONFIG_SOFTWARE_H






/**
 *@brief gprs 的配置参数. 
 *
 *@detail 协议号，电话号码，ip地址，缓存大小的配置。 
 */
typedef struct 
{
    char serialnum[16];          ///<	系列号
    char protocoltype[16];       ///<　协议号
    char ipaddr[16];             ///<	IP地址
    char portnum[16];            ///<	
    char telnum[16];             ///<	电话号码
    int bufsize;            	///<	缓存大小

}ConfGprs;

/** 配置单元的管擦者要实现的更新接口
 * 当配置发生变化时调用.
 *
 */
typedef void (*confUpdate)(void);



extern ConfGprs g_config_data;

void set_default_config_data(void);
#endif