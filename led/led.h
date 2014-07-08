#ifndef LED_H
#define LED_H

#include "stm32f10x_gpio.h"

typedef enum LED{
	LED1,
	LED2,
	LED3,
	LED4
}LED;

void led_init();
void led_on(LED led);
void led_off(LED led);
void led_toggle(LED led);

#endif /* LED_H */
