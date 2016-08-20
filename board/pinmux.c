/**
  ******************************************************************************
  * @file    pinmux.c
  * @author  sundh
  * @version V0.1.1
  * @date    2016-7-30	
  * @brief   配置Stm32的外设的引脚.	
	* 
	*
  ******************************************************************************
  * @attention
  *
  *
  * <h2><center>&copy; 一个居中的标题 </center></h2>
  ******************************************************************************
	---------------------------------------------------------------------------- \n
	  Change History :                                                           \n
	  <Date>      <Version> | <Author>       | <Description>                    \n
	---------------------------------------------------------------------------- \n
	  2016/07/30 | 0.1.1   	| sundh     		| Create file                      \n
	---------------------------------------------------------------------------- \n
  */


#include "pinmux.h"
#include "stm32f10x_gpio.h"





/** 
* @brief 配置uart1的引脚。
*
*根据SIM800A开发板的原理图，引脚为:rx PA10 tx PA9
* @param void    
*           
*
* @return 
*        -<em> 负数 :</em> fail \n
*        -<em> ERR_OK :</em> succeed
*/
err_t conf_uart1_pin(void)
{
	GPIO_InitTypeDef	rx_pin;
	GPIO_InitTypeDef	tx_pin;
	
	
	rx_pin.GPIO_Pin = GPIO_Pin_10;
	rx_pin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &rx_pin);
	
	tx_pin.GPIO_Pin = GPIO_Pin_9;
	tx_pin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &tx_pin);
	
	return ERR_OK;
	
}


/** 
* @brief 配置uart3的引脚。
*
*根据SIM800A开发板的原理图，引脚为:rx PB11 tx PB10
* @param void    
*           
*
* @return 
*        -<em> 负数 :</em> fail \n
*        -<em> ERR_OK :</em> succeed
*/
err_t conf_uart3_pin(void)
{
	GPIO_InitTypeDef	rx_pin;
	GPIO_InitTypeDef	tx_pin;
	
	
	rx_pin.GPIO_Pin = GPIO_Pin_11;
	rx_pin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &rx_pin);
	
	tx_pin.GPIO_Pin = GPIO_Pin_10;
	tx_pin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &tx_pin);
	
	return ERR_OK;
	
}



