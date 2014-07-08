
#include <stdio.h>
#include "led.h"

int main()
{
	led_init();
	led_on(LED1);
	while(1)
	{

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
