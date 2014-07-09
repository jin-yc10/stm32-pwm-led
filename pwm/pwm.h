#ifndef PWM_H_
#define PWM_H_

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "led.h"

void PWM_init( void );
void set_ratio( int ratio);
void step_ratio( void );
#endif
