#include "kernel.h"

#define NUM_OF_THREADS      3
#define STACKSIZE           400

#define BUS_FREQ            16000000
uint32_t MILLIS_PRESCALER;

#define CTRL_E		(1U<<0) // Enable SysTick Counter (CSR = Control and Status Register)
#define CTRL_CS		(1U<<2) // Clocksource bit (processor/external)
#define CTRL_TIE	(1U<<1) // Enables SysTick exception request
#define CTRL_CF		(1U<<16)// CountFlag
#define SYSTICK_RST 0

void scheduler_launch(void);


struct tcb { //Thread Control Block
	int32_t *stackPt;
	struct tcb *nextPt;
};

typedef struct tcb tcbType;

tcbType tcbs[NUM_OF_THREADS];
tcbType *currentPt;

int32_t TCB_STACK[NUM_OF_THREADS][STACKSIZE];

void kernel_stack_init(int i)
{
    tcbs[i].stackPt = &TCB_STACK[i][STACKSIZE - 16]; // Stackpointer
    // Sets bit 24 (T-bit) in PSR to 1, to operate in thumb mode
    TCB_STACK[i][STACKSIZE - 1] = (1U<<24);

    // Debug: Setting registers to a noticeable value
    TCB_STACK[i][STACKSIZE - 3] = 0xAAAAAAAA; // R14
    TCB_STACK[i][STACKSIZE - 4] = 0xAAAAAAAA; // R12
    TCB_STACK[i][STACKSIZE - 5] = 0xAAAAAAAA; // R3
    TCB_STACK[i][STACKSIZE - 6] = 0xAAAAAAAA; // R2
    TCB_STACK[i][STACKSIZE - 7] = 0xAAAAAAAA; // R1
    TCB_STACK[i][STACKSIZE - 8] = 0xAAAAAAAA; // R0
    TCB_STACK[i][STACKSIZE - 9] = 0xAAAAAAAA; // R11
    TCB_STACK[i][STACKSIZE - 10] = 0xAAAAAAAA; // R10
    TCB_STACK[i][STACKSIZE - 11] = 0xAAAAAAAA; // R9
    TCB_STACK[i][STACKSIZE - 12] = 0xAAAAAAAA; // R8
    TCB_STACK[i][STACKSIZE - 13] = 0xAAAAAAAA; // R7
    TCB_STACK[i][STACKSIZE - 14] = 0xAAAAAAAA; // R6
    TCB_STACK[i][STACKSIZE - 15] = 0xAAAAAAAA; // R5
    TCB_STACK[i][STACKSIZE - 16] = 0xAAAAAAAA; // R4
}

uint8_t kernel_add_threads(void(*task0)(void), void(*task1)(void), void(*task2)(void))
{
    // Global Interrupts
    __disable_irq();

    tcbs[0].nextPt = &tcbs[1];
    tcbs[1].nextPt = &tcbs[2];
    tcbs[2].nextPt = &tcbs[0];

    kernel_stack_init(0);
    // Initialize PC
    TCB_STACK[0][STACKSIZE - 2] = (int32_t)(task0);

    kernel_stack_init(1);
    // Initialize PC
    TCB_STACK[1][STACKSIZE - 2] = (int32_t)(task1);

    kernel_stack_init(2);
    // Initialize PC
    TCB_STACK[2][STACKSIZE - 2] = (int32_t)(task2);


    // Start form thread 0
    currentPt = &tcbs[0];

    // Global Interrupts
    __enable_irq();

    return 1;
}

void kernel_init(void)
{
    MILLIS_PRESCALER = (BUS_FREQ/1000);
}

void kernel_launch(uint32_t quanta)
{
    // Reset SysTick
    SysTick->CTRL = SYSTICK_RST;

    // Clear SysTick Current Value Register
    SysTick->VAL = 0;

    // Load Quanta
    SysTick->LOAD = (quanta * MILLIS_PRESCALER) - 1;

    // Set SysTick to low priority
    NVIC_SetPriority(SysTick_IRQn, 15);

    // Enable SysTick select Clocksource
    SysTick->CTRL = CTRL_CS;
    SysTick->CTRL |= CTRL_E;

    // Enabling SysTick Interrupt
    SysTick->CTRL |= CTRL_TIE;

    // Launch Scheduler
    scheduler_launch();
}

     // Following registers are stored automatically on exception R0 - R3, R12, LR, PC, PSR

__attribute__((naked)) void SysTick_Handler(void)
{
    // Suspend Current Thread
    // Global Interrupts
    __asm("CPSID I");

    // Save R4-R11
    __asm("PUSH {R4-R11}");

    // Load address of currentPt into R0
    __asm("LDR R0, =currentPt");

    // R1=currentPt to current TCB
    __asm("LDR R1, [R0]");

    // Cortex-M SP equals R1, save SP into TCB's first variable, stackPt
    __asm("STR SP, [R1]");

    
    // Retrieve Second Thread
    // Load r1 from TCB's second variable nextPt
    __asm("LDR R1, [R1, #4]");

    // Store R1 at address = R0, currentPt = r1, currentPt = nextPt
    __asm("STR R1, [R0]");

     // Load SP of new TCB, SP = currentPt -> stackPt
     __asm("LDR SP, [R1]");

     // Restore R4-R11
     __asm("POP {R4-R11}");

     // Global Interrupts
     __asm("CPSIE I");

     // Return from exception and restore R0 - R3, R12, LR, PC, PSR
     __asm("BX LR");
}

void scheduler_launch(void)
{
    // Load address of currentPt
    __asm("LDR R0, =currentPt");

    // Load the value of currentPt
    __asm("LDR R2, [R0]");

    // Load TCB Stack into SP
    __asm("LDR SP, [R2]");

    // Restore R4-11
    __asm("POP {R4-R11}");
    
    // Restore R12
    __asm("POP {R12}");
    // Restore R0 - R3
    __asm("POP {R0-R3}");

    // Skipping LR
    __asm("Add SP, SP, #4");

    // Create a new start location by popping LR
    __asm("POP {LR}");

    // Skip PSR
    __asm("ADD SP, SP, #4");

    // Global Interrupts
    __asm("CPSIE I");
    // Return
    __asm("BX LR");

    

}

