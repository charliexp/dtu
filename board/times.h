#ifndef _TIMERS_H_
#define _TIMERS_H_
#define MAX_COMMA 256
typedef struct TIME2_T
{
    unsigned int    time_overflow_1s;
    unsigned int    time_overflow_100ms;
    unsigned char   flag;
    unsigned int    send_gprs_position;
}TIME2_T;

extern void Delay(unsigned long nCount);
extern void delay_GSM(unsigned int i);
extern void delay_1ms(unsigned int i);


extern void clean_time2_flags(void);
extern unsigned char is_enable_send_gprs_position(void);

#endif
