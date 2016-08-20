#ifndef __ERR_HEAD_H
#define __ERR_HEAD_H


typedef int err_t;


#define ERR_OK 									0 					/* No error, everything OK. */
#define ERR_UNKOWN     					-1    			/* δ֪���� ,�޷�ָ��ĳ���������ʱʹ��   */
#define ERR_BAD_PARAMETER     	-2    			/*       */
#define ERR_ERROR_INDEX    	 		-3    			/*       */
#define ERR_UNINITIALIZED     	-4    			/* �����û�гɹ���ʼ����ʱ���ʹ�õ�ʱ��ָ��     */
#define ERR_CATASTROPHIC_ERR		-5 					/* �����Դ���			*/
#define ERR_MEM_UNAVAILABLE			-6					/* �ڴ治�ɻ�ȡ			*/
#define ERR_RES_UNAVAILABLE			-7					/* ��Դ���ɻ�ȡ			*/


#define MAX_ERROR_COUNT 30000

#endif
