#include "led.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void led_init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // ENABLE THE CLOCK

	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	gpio_struct.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_struct);
}

void led_on(LED led)
{
	switch(led)
	{
	case LED1:
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		break;
	case LED2:
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		break;
	case LED3:
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		break;
	case LED4:
		GPIO_SetBits(GPIOA, GPIO_Pin_7);
		break;
	}
}

void led_off(LED led)
{
	switch(led)
	{
	case LED1:
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		break;
	case LED2:
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		break;
	case LED3:
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		break;
	case LED4:
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		break;
	}
}

void led_toggle(LED led)
{
	uint16_t pin;
	switch(led)
	{
	case LED1:
		pin = GPIO_Pin_4;
		break;
	case LED2:
		pin = GPIO_Pin_5;
		break;
	case LED3:
		pin = GPIO_Pin_6;
		break;
	case LED4:
		pin = GPIO_Pin_7;
		break;
	}
	GPIOA->ODR ^= pin;
}


