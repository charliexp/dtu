#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "err_head.h"
#include "gprs.h"
#include "gprs_uart.h"
#include "config_hardware.h"
#include "times.h"

int num_of_sms;
#define SMS_CMD_LEN 30
char at_readsms[SMS_CMD_LEN];
char tpy_sms_content[SMS_CMD_LEN];
char tpy_send_tel_num[SMS_CMD_LEN];
int Gprs_err;

unsigned char is_gprs_mode_ok = 1;                  //gprs start succeed
unsigned char is_gprs_mode_start_succeed = 0;       //gprs connect ok
SIM_STATUS current_status = INIT0 ;


//REG
#define ATE0_CMD "ATE0\r\n"           		/// ��ֹ����
#define CREG_CMD "AT+CREG?\x00D\x00A"       /// ��ѯ����ע�����
#define CGMM_CMD "AT+CGMM\x00D\x00A"
#define SIMCARD_CMD "AT+CPIN?\x00D\x00A"


//LD GPRS
#define GPRS_QD "AT+CSTT\x00D\x00A"         /// GPRS����
#define GPRS_JH "AT+CIICR\x00D\x00A"        /// �ƶ���������,����
//LGL GPRS
#define GPRS_DEF_PDP "AT+CGDCONT=1,\"IP\",\"CMNET\"\x00D\x00A"  /// �����
#define GPRS_ACT_PDP "AT+CGATT=1\x00D\x00A"                     /// GPRS����PDP

#define GPRS_CMNET_APN "AT+CIPCSGP=1,\"CMNET\"\x00D\x00A"       /// ����GPRSģʽ


//CONNECT... GPRS
#define GPRS_BJ_ADDR "AT+CIFSR\x00D\x00A"   /// ��ȡ����IP
#define GPRS_TCP1 "AT+CIPSTART="            /// ����һ��IP����
#define GPRS_TCP2 PROTOTOCOL
#define GPRS_TCP3 IPADDR
#define GPRS_TCP4 PORTNUM

#define PM "^SIM800A^"
//SEND  GPRS
#define GPRS_SEND_DATA "AT+CIPSEND\x00D\x00A"


//SEND SMS
#define GSM_MSG_MODE "AT+CMGF=1\x00D\x00A"
//#define GSM_CENTER_NUM "AT+CSCA=\"+8613800512500\"\x00D\x00A"
#define GSM_CHAR_MODE "AT+CSCS=\"GSM\"\x00D\x00A"
#define GSM_SEND_TEXT "AT+CMGS=\"+8613512963352\"\x00D\x00A"
//READ SMS
#define SMSCAT "CMTI: \"SM\","
#define SMSCATRHOS "+CMT:"
//ds18b20
#define NO_SENSOR "no sensor"

char g_gprs_conn_ok=0;	   //GPRS��������״̬
char ibusy  = 0;		   //�ڷ������ݵ�ʱ��,������ֹͣ

void start_gprs_mode(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_0);
    delay_GSM(100);
    GPIO_SetBits(GPIOB,GPIO_Pin_0);
    delay_GSM(10000);
    GPIO_ResetBits(GPIOB,GPIO_Pin_0);
}


/// ����һ��IP���� AT+CIPSTART=��TCP��,��211.136.42.12��,��2020��
void __GPRS_TCPIP()
{//AT+CMGR=1

    uart_string_send(GPRS_TCP1);
    uart_data_send(0x22);
    uart_string_send(g_config_data.protocoltype);
    uart_data_send(0x22);
    uart_data_send(',');
    uart_data_send(0x22);
    uart_string_send(g_config_data.ipaddr);
    uart_data_send(0x22);
    uart_data_send(',');
    uart_data_send(0x22);
    uart_string_send(g_config_data.portnum);
    uart_data_send(0x22);
    uart_data_send(0x0D);
    uart_data_send(0x0A);
    PUT("destination address:");
    PUT(g_config_data.ipaddr);
  
    delay_GSM(3000);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

static void S_GSM_INIT0()
{

    PUT_2("S_GSM_INIT0 \r\n");
    clear_buf_uart3();
    uart_string_send(ATE0_CMD);		  //�رջ���
    current_status = RST ;
}
static void S_RST()
{
    PUT_2(buf_uart3.buf);
    if(buf_uart3.buf[2] == 'O' &&
       buf_uart3.buf[3] == 'K')
    {

        PUT_2("S_RST OK \r\n");
        is_gprs_mode_start_succeed = 1;		 //GPRSģ��͵�Ƭ���Ĵ���3�Ѿ�ͨ������
        clear_buf_uart3();
        current_status = SIMCARD ;
        uart_string_send(SIMCARD_CMD);

    }
	else
	{
        delay_GSM(5000);
        clear_buf_uart3();
        current_status = RST ;
        uart_string_send(ATE0_CMD);
    }
}

static void S_SIMCARD_CMD()
{
    char *pp = NULL;
    PUT(buf_uart3.buf);
    pp = strstr((const char*)buf_uart3.buf,"OK");
    if(pp)
    {
        PUT_2("SIMCARD_CMD OK \r\n");
        clear_buf_uart3();
        current_status = CREG ;
        uart_string_send(CREG_CMD);
    }
	else
	{
        PUT_2("SIMCARD_CMD Gprs_err \r\n");
        clear_buf_uart3();
        current_status = SIMCARD ;
        uart_string_send(SIMCARD_CMD);
    }
}

static void S_CREG()
{
    if(((buf_uart3.buf[9]=='0')&&
        (buf_uart3.buf[11]=='1'))||
       ((buf_uart3.buf[9]=='0')&&
        (buf_uart3.buf[11]=='5')))
    {
        PUT_2("S_REG OK \r\n");
        current_status = INIT_FINISH_OK;
    }else{
        PUT_2(buf_uart3.buf);
        PUT_2("S_REG Gprs_err \r\n");

        debug_put_word(buf_uart3.buf[9]);
        debug_put_word(buf_uart3.buf[11]);

        clear_buf_uart3();
        current_status = CREG ;
        uart_string_send(CREG_CMD);
    }
}


void init_gprs(void)
{

    PUT("start init GPRS\r\n");
    current_status = INIT0;

    while(1)
    {
        Gprs_err ++;
        if(Gprs_err>MAX_ERROR_COUNT)
        {
            Gprs_err = 0 ;
            is_gprs_mode_ok = 0;
            delay_GSM(100000);
            break;
        }

        if(is_gprs_mode_start_succeed)
        {
            ;
        }

        delay_GSM(1000);

        switch(current_status)
        {
        case INIT0:
            S_GSM_INIT0();
            break ;

        case RST:
            S_RST();
            break ;

        case SIMCARD:
            S_SIMCARD_CMD();
            break ;

        case CREG:
            S_CREG();
            break ;

        case INIT_FINISH_OK:
            return ;

        default:
            clear_buf_uart3();
            break ;
        }
    }
    return ;
}

 ///////////////////////////////////////////////////////////////////////////

static void S_START_OPEN_GPRS_S()               //��ʼGPRS ���SIM����
{
    PUT_2("S_START_OPEN_GPRS_S OK \r\n");

    clear_buf_uart3();
    current_status = GPRS_DEF_PDP_S ;           //����PDP�ƶ�����
    uart_string_send(SIMCARD_CMD);
}


static void S_GPRS_DEF_PDP_S()                  //���SIM�� ����PDP
{
    char *t = NULL ;

    t = strstr((const char*)buf_uart3.buf,"OK");
    if(t)
    {
        PUT_2("SIMCARD_CMD OK \r\n");
        clear_buf_uart3();
        current_status = GPRS_ACT_PDP_S ;
        uart_string_send(GPRS_DEF_PDP);
    }
    else
    {
        PUT_2("SIMCARD_CMD NO \r\n");
        clear_buf_uart3();
        uart_string_send(SIMCARD_CMD);
    }
}

static void S_GPRS_ACT_PDP_S()                  //�ж϶���PDP ����PDP
{
    if((buf_uart3.buf[2]=='O')&&(buf_uart3.buf[3]=='K'))
    {
        PUT_2("S_GPRS_DEF_PDP_S OK \r\n");
        clear_buf_uart3();
        current_status = GPRS_ACT_PDP_S_RET ;       // ���ͼ���
        uart_string_send(GPRS_ACT_PDP);
    }
    else
    {
        PUT_2("S_GPRS_DEF_PDP_S NO \r\n");

        clear_buf_uart3();
        uart_string_send(GPRS_DEF_PDP);			//�����

    }
}

static void S_GPRS_ACT_PDP_S_RET()                  //�жϼ���
{
    if((buf_uart3.buf[2]=='O')&&(buf_uart3.buf[3]=='K'))
    {
        PUT_2("S_GPRS_ACT_PDP_S_RET OK \r\n");
        clear_buf_uart3();
        current_status = GPRS_OPEN_FINISH;
    }
    else
    {
        PUT_2(buf_uart3.buf);
        PUT_2("S_GPRS_ACT_PDP_S_RET NO \r\n");
        clear_buf_uart3();
		uart_string_send(GPRS_ACT_PDP);
    }
}

void open_gprs_simple(void)
{

    if(!is_gprs_mode_ok)
        return ;

    current_status = INIT_FINISH_OK;

    while(1)
    {
        Gprs_err ++;
        if(Gprs_err>MAX_ERROR_COUNT)
        {
            Gprs_err = 0 ;
            delay_GSM(100000);
            break;
        }

        delay_GSM(1000);


        switch(current_status)
        {
        case INIT_FINISH_OK:
            S_START_OPEN_GPRS_S();		   //�ٴη��Ϳ�״̬
            break ;

        case  GPRS_DEF_PDP_S:
            S_GPRS_DEF_PDP_S();			   //���ͽ����
            break ;

        case  GPRS_ACT_PDP_S:
            S_GPRS_ACT_PDP_S();			//���ͼ�������
            break ;

        case GPRS_ACT_PDP_S_RET:
            S_GPRS_ACT_PDP_S_RET();
            break ;

        case GPRS_OPEN_FINISH:
            return ;
        default:
            clear_buf_uart2();
            break ;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////
static void S_GPRS_OPEN_FINISH()
{
    clear_buf_uart3();
    current_status = TCPIP_BJ_ADDR ;
    PUT_2("S_GPRS_OPEN_FINISH\r\n");
}

static void S_TCPIP_BJ_ADDR()
{
    clear_buf_uart3();
    current_status = TCPIP_CONNECT ;
    uart_string_send(GPRS_BJ_ADDR);		  //��ȡ����IP��ַ
    PUT_2("S_TCPIP_BJ_ADDR\r\n");
}

static void  S_TCPIP_CONNECT()
{		
	clear_buf_uart3();
    current_status = TCP_IP_CONNECTING ;
    __GPRS_TCPIP();							   //����TCPIPͨ��
}

static void S_TCP_IP_CONNECTING()
{

    char *ret_val = NULL;
	char *aret_val = NULL;
	char *bret_val = NULL ;
    static unsigned int count = 0 ;

    ret_val =  strstr((const char*)buf_uart3.buf,"CONNECT OK");
    aret_val = strstr((const char*)buf_uart3.buf,"ALREADY CONNECT");
	bret_val = strstr((const char*)buf_uart3.buf,"CONNECT FAIL");
	
    PUT("\r\nS_TCP_IP_CONNECTING...\r\n");
	PUT(buf_uart3.buf);
	g_gprs_conn_ok = 0;
	if (ret_val)				  					 //��ѯ��CONNECT�ķ���
    {
        current_status = TCP_IP_OK ;
		g_gprs_conn_ok=1;
		return ;
    }
    if ((ret_val||aret_val)&&!bret_val)				  					 //��ѯ��CONNECT�ķ���
    {
        current_status = TCP_IP_OK ;
		g_gprs_conn_ok=1;
    }
    else
    {
        count ++ ;
        delay_GSM(5000);
        if (count == 30)
        {
            current_status = TCP_IP_NO ;
            count = 0 ;
			return ;
        }
		clear_buf_uart3();
    	current_status = TCP_IP_CONNECTING ;
    	__GPRS_TCPIP();	

    }
}


void creat_tcp()
{
    if(!is_gprs_mode_ok)
        return ;

    while(1)
    {
        Gprs_err ++;

        if(Gprs_err>MAX_ERROR_COUNT)
        {
            Gprs_err = 0 ;
            break;
        }

        delay_GSM(1000);
        switch(current_status)
        {
        case GPRS_OPEN_FINISH:
            S_GPRS_OPEN_FINISH();
            break ;

        case TCPIP_BJ_ADDR:
            S_TCPIP_BJ_ADDR();
            break ;

        case TCPIP_CONNECT:
            S_TCPIP_CONNECT();
            break ;

        case TCP_IP_CONNECTING:
            S_TCP_IP_CONNECTING();
            break ;

        case TCP_IP_OK :
            clear_buf_uart3();
            return ;
        case  TCP_IP_NO:
            clear_buf_uart3();
            return ;
        default:
            clear_buf_uart3();
            break ;
        }
    }
}



void send_gprs_data(char * buf , unsigned int count)
{
    unsigned int i ,j;
    if (current_status != TCP_IP_OK)        // ���Э��û�����ӳɹ�ֱ�ӷ���
        return ;

	ibusy = 1;
#if 1
    uart_string_send(GPRS_SEND_DATA);		  //������������ ע��û��������
    delay_GSM(2000);

    for( j = 0 ;j < count ; j ++)
    {
        for ( i = 0 ; i < strlen((const char*)buf) ; i ++)
        {
            uart_data_send(buf[i]);
        }
    }

    uart_data_send(0x1A);  //LF			  //û��������һ��Ҫ��1A��ʾ����
#endif
	ibusy = 0;
}

void gprs_heart(char *w,int t)										 //�¶Ⱥ���������
{	
	char *ptt = NULL;
	char tstr[BUFLEN];
	char tbuf[BUFLEN];
	memset(tbuf,0,BUFLEN);
	memset(tstr,0,BUFLEN);
	sprintf(tstr,"%d",t);
	ptt =  strstr((const char*)g_config_data.serialnum,"temp");		//��⵽�¶����к�
    if(ptt)
	{
		if(strlen(w)>0)
			send_gprs_data(w,1);									//�����¶�
		else
		    send_gprs_data(NO_SENSOR,1);
	}
	else
	{
		strcat(tbuf,"SN:");
		strcat(tbuf,g_config_data.serialnum);
		strcat(tbuf," BEAT:");
		strcat(tbuf,tstr);
		send_gprs_data(tbuf,1);										 //�������������к�
	}
}



static void S_GSM_MSG_MODE_S()
{

    PUT("S_GSM_MSG_MODE_S OK \r\n");
    clear_buf_uart3();
    current_status = GSM_MSG_MODE_S ;           //����PDP�ƶ�����
    uart_string_send(GSM_MSG_MODE);

}

static void S_GSM_CHAR_MODE_S()
{
    if((buf_uart3.buf[2]=='O')&&(buf_uart3.buf[3]=='K'))
    {
        PUT("S_GSM_CHAR_MODE_S OK \r\n");
        clear_buf_uart3();
        current_status = GSM_CHAR_MODE_S;
        uart_string_send(GSM_CHAR_MODE);
    }
    else
    {
        PUT("S_GSM_CHAR_MODE_S NO \r\n");
        clear_buf_uart3();
        uart_string_send(GSM_MSG_MODE);
    }
}

static void S_GSM_CHAR_MODE_RET_S()
{
    if((buf_uart3.buf[2]=='O')&&(buf_uart3.buf[3]=='K'))
    {
        PUT("S_GSM_CHAR_MODE_RET_S OK \r\n");
        clear_buf_uart3();
        current_status = GSM_TEXT_MODE_FINISH;
    }
    else
    {
        PUT("S_GSM_CHAR_MODE_RET_S NO \r\n");
        clear_buf_uart3();
        uart_string_send(GSM_CHAR_MODE);
    }
}


static void init_sms_to_send()
{
    current_status = GSM_SEND_TEXT_S;

    while(1)
    {
        Gprs_err ++;
        if(Gprs_err>MAX_ERROR_COUNT)
        {
            Gprs_err = 0 ;
            break;
        }
        delay_GSM(1000);
        switch(current_status)
        {
        case GSM_SEND_TEXT_S:
            S_GSM_MSG_MODE_S();
            break ;

        case GSM_MSG_MODE_S:
            S_GSM_CHAR_MODE_S();
            break ;

        case GSM_CHAR_MODE_S:
            S_GSM_CHAR_MODE_RET_S();
            break ;

        case GSM_TEXT_MODE_FINISH:
            break ;
        default:
            clear_buf_uart3();
            break ;
        }
    }
}

void send_gsm_text(unsigned char * buf , unsigned int count)
{
    unsigned int i ;
    char send_sms_cmd_num[SMS_CMD_LEN];
    memset((void*)send_sms_cmd_num,0,SMS_CMD_LEN);

    if(!is_gprs_mode_ok)
        return ;

    init_sms_to_send();
    if(current_status != GSM_TEXT_MODE_FINISH)
        return ;

    PUT((char *)buf);

    PUT("\r\nTEL-\r\n");
    PUT(tpy_send_tel_num);
    PUT("-END\r\n");

    if(strlen(tpy_send_tel_num) != 11)
        uart_string_send(GSM_SEND_TEXT);
    else
    {
        sprintf(send_sms_cmd_num,"AT+CMGS=\"+86%s\"\x00D\x00A",tpy_send_tel_num);
        PUT(send_sms_cmd_num);
        uart_string_send(send_sms_cmd_num);
    }
    delay_GSM(100);
    for( i = 0 ;i < count ; i ++)
    {
        for ( i = 0 ; i < strlen((const char*)buf) ; i ++)
        {
            uart_data_send(buf[i]);
        }
    }

    delay_GSM(100);
    send_data_uart1(0X1A);
    delay_GSM(5000);
}



unsigned char is_gprs_mode_status_ok(void)
{
    return is_gprs_mode_ok;
}

