/**
  ******************************************************************************
  * @file    TIM/TIM_TimeBase/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    24-July-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"

/** @addtogroup STM32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_TimeBase
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t capture = 0;


extern __IO uint8_t exti_flag;
extern __IO uint32_t counting;

extern __IO uint8_t pressed;
extern __IO uint8_t no_exti;
extern __IO uint8_t exti_cnt;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
  if(counting++ > 199)
    counting = 0;
}

void EXTI4_15_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line8) != RESET && no_exti == 0)
  {
    pressed = 1;
    exti_flag = 8;
    EXTI_ClearITPendingBit(EXTI_Line8);
  }
  else{
  exti_cnt ++;
  EXTI_ClearITPendingBit(EXTI_Line8);
  }

	if(EXTI_GetITStatus(EXTI_Line6) != RESET && no_exti == 0)
  {
    pressed = 1;
    exti_flag = 6;
    EXTI_ClearITPendingBit(EXTI_Line6);
  }
  else{EXTI_ClearITPendingBit(EXTI_Line6);}

	if(EXTI_GetITStatus(EXTI_Line5) != RESET && no_exti == 0)
  {
    pressed = 1;
    exti_flag = 5;
    EXTI_ClearITPendingBit(EXTI_Line5);
  }
	else{EXTI_ClearITPendingBit(EXTI_Line5);}

}


void TIM3_IRQHandler(void)
{
  pressed ++;
  if (TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC4);

    /* LED4 toggling with frequency = 439.4 Hz */
    capture = TIM_GetCapture4(TIM3);
    TIM_SetCompare4(TIM3, capture + 6826);
//    if(EXTI_GetITStatus(EXTI_Line8) == RESET )
//    release = 1;
  }
/*  else if(TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);
  }
  else if(TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
  }
  else if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
  }*/
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
