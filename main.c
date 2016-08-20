/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "config_hardware.h"
#include "chipset.h"
#include "pinmux.h"
#include "stm32_eval.h"
#include "stdio.h"

#include "subsys_commu.h"
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(USART1, (uint8_t) ch);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
    }

    return ch;
}
/*
 * main: initialize and start the system
 */
int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS
	
	
  // initialize peripherals here
	///< 配置系统时钟到72MHZ
	RCC_Configuration();
	
	NVIC_Configuration();
	
	GPIO_Configuration();
	Init_TIM2();
	STM_EVAL_COMInit(COM1, &USART_InitStructure);
	printf("[main] DTU project start...\r\n");
	USART_Configuration();
	
  // create 'thread' functions that start executing,
  // example: tid_name = osThreadCreate (osThread(name), NULL);

	///< 启动通讯子系统
	printf("[main] launch gprs launch...\r\n");
	Init_CMM_Thread();
  osKernelStart ();                         // start thread execution 
}
