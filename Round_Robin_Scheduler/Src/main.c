#include "led.h"
#include "uart.h"
#include "timebase.h"
#include "kernel.h"

#define QUANTA 10

typedef uint32_t TaskProfiler;

TaskProfiler Task0_Profiler, Task1_Profiler, Task2_Profiler, Task3_Profiler, Task4_Profiler, Task5_Profiler, Task6_Profiler, Task7_Profiler, Task8_Profiler, Task9_Profiler;





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

void task3(void)
{
	while(1)
	{
		Task3_Profiler++;
	}
}

void task4(void)
{
	while(1)
	{
		Task4_Profiler++;
	}
}

void task5(void)
{
	while(1)
	{
		Task5_Profiler++;
	}
}

void task6(void)
{
	while(1)
	{
		Task6_Profiler++;
	}
}

void task7(void)
{
	while(1)
	{
		Task7_Profiler++;
	}
}

void task8(void)
{
	while(1)
	{
		Task8_Profiler++;
	}
}

void task9(void)
{
	while(1)
	{
		Task9_Profiler++;
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
    kernel_add_threads(&task0, &task1, &task2, &task3, &task4, &task5, &task6, &task7, &task8, &task9);

    printf("Added Threads \n\r");
    // Set RoundRobin Time Quanta
	kernel_launch(QUANTA);
}
