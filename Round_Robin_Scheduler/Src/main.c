#include "led.h"
#include "uart.h"
#include "timebase.h"
#include "kernel.h"

#define QUANTA 10

typedef uint32_t TaskProfiler;

TaskProfiler Task0_Profiler, Task1_Profiler, Task2_Profiler;



void task_hello0(void);
void task_hello1(void);
void task_hello2(void);



void task0(void)
{
	while(1)
	{
		Task0_Profiler++;
	}
}

void task1(void)
{
	while(1)
	{
		Task1_Profiler++;
	}
}

void task2(void)
{
	while(1)
	{
		Task2_Profiler++;
	}
}



int main (void)
{
	led_init();
	uart_tx_init();
    timebase_init();
    kernel_init();

    printf("Starting \n\r");

    // Add Threads
    kernel_add_threads(&task0, &task1, &task2);

    printf("Added Threads \n\r");
    // Set RoundRobin Time Quanta
	kernel_launch(QUANTA);
}
