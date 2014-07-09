/*
 * pwm.c
 *
 *  Created on: 2014年7月9日
 *      Author: jin-yc10
 */
#ifndef PWM_C
#define PWM_C
#include "pwm.h"
#include "stm32f10x_it.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"

void RCC_Configuration(void);
void TIM_Configuration(void);
void GPIO_Configuration(void);

void PWM_init(void)
{
	RCC_Configuration();
	TIM_Configuration();
	GPIO_Configuration();
}

void RCC_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // ENABLE THE CLOCK
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );
}

/**
  * @brief  configure the PD12~15 to Timers
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure); // Reset init structure

    // Setup Blue & Green LED on STM32-Discovery Board to use PWM.
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;            // Alt Function - Push Pull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOA, &GPIO_InitStructure );
}

/**
  * @brief  configure the TIM4 for PWM mode
  * @param  None
  * @retval None
  */
void TIM_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;

    // Let PWM frequency equal 100Hz.
    // Let period equal 1000. Therefore, timer runs from zero to 1000. Gives 0.1Hz resolution.
    // Solving for prescaler gives 240.
    TIM_TimeBaseStructInit( &TIM_TimeBaseInitStruct );
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV4;
    TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM3, &TIM_TimeBaseInitStruct );

    TIM_OCStructInit( &TIM_OCInitStruct );
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;

    // Initial duty cycle equals 0%. Value can range from zero to 65535.
    //TIM_Pulse = TIM4_CCR1 register (16 bits)
    TIM_OCInitStruct.TIM_Pulse = 100 - 1; //(0=Always Off, 65535=Always On)

    TIM_OC1Init( TIM3, &TIM_OCInitStruct ); // Channel 1  LED
    TIM_OC2Init( TIM3, &TIM_OCInitStruct ); // Channel 2  LED
    TIM_OC3Init( TIM3, &TIM_OCInitStruct ); // Channel 3  LED
    TIM_OC4Init( TIM3, &TIM_OCInitStruct ); // Channel 4  LED

    TIM_Cmd( TIM3, ENABLE );
}

/**
  * @brief  Configure the TIM IRQ Handler.
  * @param  None
  * @retval None
  */
void TIM_Config(void)
{

}

void set_ratio(int ratio)
{

}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

#endif
