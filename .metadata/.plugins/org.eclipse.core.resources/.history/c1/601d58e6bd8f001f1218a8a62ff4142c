#include "led.h"
#include "uart.h"
#include "timebase.h"

int main (void)
{
	led_init();
	uart_tx_init();
    timebase_init();

	int j = 0;

	while (1)
	{
		printf("Second: %i  \n\r", j);
		j += 5;
		delay(5);
	}
}
