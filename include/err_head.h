#ifndef __ERR_HEAD_H
#define __ERR_HEAD_H


typedef int err_t;


#define ERR_OK 									0 					/* No error, everything OK. */
#define ERR_UNKOWN     					-1    			/* 未知错误 ,无法指定某类错误类型时使用   */
#define ERR_BAD_PARAMETER     	-2    			/*       */
#define ERR_ERROR_INDEX    	 		-3    			/*       */
#define ERR_UNINITIALIZED     	-4    			/* 在组件没有成功初始化的时候就使用的时候指定     */
#define ERR_CATASTROPHIC_ERR		-5 					/* 灾难性错误			*/
#define ERR_MEM_UNAVAILABLE			-6					/* 内存不可获取			*/
#define ERR_RES_UNAVAILABLE			-7					/* 资源不可获取			*/


#define MAX_ERROR_COUNT 30000

#endif
