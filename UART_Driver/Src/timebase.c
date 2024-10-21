#include "timebase.h"
#include "stm32f446xx.h"

#define ONE_SEC_LOAD 16000000 //16 MHz = SYS_FREQ

#define CSR_E		(1U<<0) // Enable SysTick Counter (CSR = Control and Status Register)
#define CSR_CS		(1U<<2) // Clocksource bit (processor/external)
#define CSR_TIE		(1U<<1) // Enables SysTick exception request
#define CSR_CF		(1U<<16)// CountFlag

#define MAX_DELAY   0xFFFFFFFFU // Maximum 32 bit number 

volatile uint32_t g_curr_tick;
volatile uint32_t g_curr_tick_p;
volatile uint32_t tick_freq = 1;

uint32_t get_tick(void)
{
    __disable_irq();
    g_curr_tick_p = g_curr_tick;
    __enable_irq();
    return g_curr_tick_p;
}

//Delays in seconds
void delay(uint32_t delay)
{
    uint32_t tickstart = get_tick();
    uint32_t wait = delay;
    // Might cause issues, better use in ms delays, right now it just adds 1 second.
    if (wait < MAX_DELAY)
    {
        wait += tick_freq;
    }
    while((get_tick() - tickstart) < wait){}

}

void tick_increment(void)
{
    g_curr_tick += tick_freq;
}


void timebase_init(void)
{
	// Load the timer with number of cycles per seconds
    SysTick->LOAD = ONE_SEC_LOAD - 1;
	// Clear SysTick Current Value Register
    SysTick->VAL = 0;
	// Select Internal Clock
    SysTick->CTRL |= CSR_CS;
	// Enable Interrupt
    SysTick->CTRL |= CSR_TIE;
	// Enable SysTick
    SysTick->CTRL |= CSR_E;
    // Enable global interrupts
    __enable_irq(); // Possibly redundant
}

void SysTick_Handler() // Interrupt handler
{
    tick_increment();
}
