/**
  ******************************************************************************
  * @file main.c
  * @brief This file contains the main function for Discover example.
  * @author STMicroelectronics - MCD Application Team
  * @version V1.0.0
  * @date 24/11/2011
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  * FOR MORE INFORMATION PLEASE READ CAREFULLY THE LICENSE AGREEMENT FILE LOCATED 
  * IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  * @image html logo.bmp
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/**
  * @addtogroup TIM4_TimeBase_InterruptConfiguration
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile bool User_Key_Pressed = 0;
u8 BlinkSpeed = 6;
u8 Counter;
u8 PeriodNumber = 0;
char *message = "Iloveyou";
int bitArr[8];
int test[8];

char *ptr;
int i;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void TIMER_Configuration(void);
void Delay (int nCount);
void bin_to_led(int);
void Turn_On_Sequence(void);
/* Public functions ----------------------------------------------------------*/
/**
  * @brief Example firmware main entry point.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void main(void)
{

  /* Configure PD0 (LED1) as output push-pull low (led switched on) */
  GPIO_Init(LED_PORT, LED_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(LED_PORT, LED_PIN_1, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(LED_PORT, LED_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(LED_PORT, LED_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);
  /* Configure PC4 (push buton) as input floating */
  GPIO_Init(BUTTON_PORT, BUTTON_PIN, GPIO_MODE_IN_PU_IT);

  
	for(ptr = message; *ptr != '\0'; ptr++){
		test[i+1] = *ptr & LOW_MASK;
		test[i]   = (*ptr & HIGH_MASK) >> 4;
		i+=2;
	}
	
	Turn_On_Sequence();
	
  while (1)
  {
		for(i=0;i<sizeof(test);i++){
			bin_to_led(test[i]);
			Delay(0xFFFFF);
			Delay(0xFFFFF);
			GPIO_Write(LED_PORT, 0xFF);
			Delay(0xFFFFF);
		}
  }
}


void Delay(int nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}


void Turn_On_Sequence(void){
	
	// I know i need to use timers and ISR to do this, but couldn't figure it out
	
	GPIO_Write(LED_PORT, 0xFF);
	Delay(0xFFFFF);
	GPIO_Write(LED_PORT, 0x00);
	Delay(0xFFFFF);
	GPIO_Write(LED_PORT, 0xFF);
	Delay(0xFFFFF);
	GPIO_Write(LED_PORT, 0x00);
	Delay(0xFFFFF);
	GPIO_Write(LED_PORT, 0xFF);
	Delay(0xFFFFF);
	GPIO_WriteLow(LED_PORT, LED_PIN_0);
	Delay(0xFFFFF);
	GPIO_WriteLow(LED_PORT, LED_PIN_1);
	Delay(0xFFFFF);
	GPIO_WriteLow(LED_PORT, LED_PIN_2);
	Delay(0xFFFFF);
	GPIO_WriteLow(LED_PORT, LED_PIN_3);
	Delay(0xFFFFF);
	GPIO_Write(LED_PORT, 0xFF);
	Delay(0xFFFFF);
	Delay(0xFFFFF);
	Delay(0xFFFFF);
}



void bin_to_led(int led){

	((led & D0_MASK) >> 0) ? GPIO_WriteLow(LED_PORT, LED_PIN_0) : GPIO_WriteHigh(LED_PORT, LED_PIN_0);
	((led & D1_MASK) >> 1) ? GPIO_WriteLow(LED_PORT, LED_PIN_1) : GPIO_WriteHigh(LED_PORT, LED_PIN_1);
	((led & D2_MASK) >> 2) ? GPIO_WriteLow(LED_PORT, LED_PIN_2) : GPIO_WriteHigh(LED_PORT, LED_PIN_2);
	((led & D3_MASK) >> 3) ? GPIO_WriteLow(LED_PORT, LED_PIN_3) : GPIO_WriteHigh(LED_PORT, LED_PIN_3);
	
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval
  * None
  */
void assert_failed(u8* file, u32 line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
