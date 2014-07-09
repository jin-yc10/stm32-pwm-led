
#include <stdio.h>
#include "led.h"
#include "pwm.h"
#include "misc.h"
#include "stm32f10x_tim.h"

#define STM32F10X_HD
#define SINGLE_TICK 1
uint32_t g_time = 0;
uint32_t last_time_100ms = 0;
void time_update( void )
{
	g_time += SINGLE_TICK;
}

int main()
{
	led_init();
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / (1000 / SINGLE_TICK));
	PWM_init();
	while(1)
	{
		if((g_time / 500) % 2 == 0)
		{
			led_on(LED3);
		}
		else
		{
			led_off(LED3);
		}
		if(last_time_100ms != g_time / 100)
		{
			last_time_100ms = g_time / 100;
			TIM3->CCR2 = (g_time / 4) % 1000;
		}
	}
	return 0;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
	while(1)
	{
	}
}
#endif /* USE_FULL_ASSERT */
