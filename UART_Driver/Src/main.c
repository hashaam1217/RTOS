#include "led.h"
#include "uart.h"

int main (void)
{
	led_init();
	uart_tx_init();

	int j = 0;

	while (1)
	{
		led_on();
		for(int i = 0; i < 450000; i++)
		{}
		led_off();
		for(int i = 0; i < 450000; i++)
		{}
		printf("STM32F446 - Hashaam Zafar %i  \n\r", j);
		j++;
	}
}
