# RTOS on ARM: Bare Metal Programming Project

### Overview

This project was created as part of my learning journey as a third-year Electrical Engineering student in 2024. The aim was to gain a deeper understanding of Real-Time Operating Systems (RTOS) on ARM processors and to explore bare-metal programming. It involved implementing basic RTOS concepts, interrupt handling, and task management on an STM32 microcontroller, using both C and Assembly.

### Features

- **Interrupt Handling:** Implemented SysTick and UART interrupts to facilitate time-based operations and serial communication.
- **LED Drivers for Serial Communication:** Developed drivers to control LEDs, providing a visual indication of the system's status and activity.
- **Task Management:** Created ten simple tasks that increment a profiler, showcasing how round-robin scheduling and task switching can be managed.
- **Bare Metal Programming:** Implemented the kernel without any operating system, controlling hardware directly using low-level C and assembly code.

### Key Components

- **Programming Language & Tools:**

  - C, Assembly
  - STM32CubeIDE
  - GDB for debugging
  - Git for version control
  - Ubuntu 24.04 as the development environment

- **RTOS Concepts Used:**

  - **Task Control Blocks (TCBs):** Used TCBs to manage task switching, store stack pointers, and implement thread control.
  - **Stack Initialization:** Created custom stack initialization routines to handle context switching in an RTOS environment.
  - **Round-Robin Scheduling:** Configured SysTick timer to provide a time quanta (`QUANTA`), allowing tasks to be switched at regular intervals.

### Code Highlights

**Main Program**

The main program initializes LED and UART drivers, sets up the kernel, and adds ten tasks for execution in a round-robin manner.

**Kernel Implementation**

The kernel manages task switching using task control blocks (TCBs) and utilizes SysTick interrupts for scheduling.

- **Stack Initialization:**

  ```c
  void kernel_stack_init(int i) {
      tcbs[i].stackPt = &TCB_STACK[i][STACKSIZE - 16];
      TCB_STACK[i][STACKSIZE - 1] = (1U << 24);  // Thumb mode
      // Set registers to noticeable values for debugging
      TCB_STACK[i][STACKSIZE - 3] = 0xAAAAAAAA; // R14
      // ...
  }
  ```

- **Context Switching:**

  SysTick_Handler and `scheduler_launch()` functions use ARM assembly for precise context switching, saving and restoring registers during task transitions.

  ```asm
  __attribute__((naked)) void SysTick_Handler(void) {
      __asm("CPSID I");
      __asm("PUSH {R4-R11}");
      // ...
      __asm("POP {R4-R11}");
      __asm("CPSIE I");
      __asm("BX LR");
  }
  ```

### Learning Outcomes

- **RTOS Basics:** Gained hands-on experience with RTOS concepts such as task scheduling, context switching, and stack management.
- **Bare-Metal Programming:** Learned to program ARM Cortex-M microcontrollers without the assistance of a pre-built operating system, directly interfacing with hardware registers.
- **Debugging with GDB:** Improved my skills in debugging embedded systems, especially in tracing interrupt handling and managing complex task interactions.

### Tools & Environment

- **Development Board:** STM32 ARM Cortex-M based microcontroller.
- **IDE & Debugger:** STM32CubeIDE and GDB for developing and debugging.
- **Operating System:** Ubuntu 24.04 for setting up the development environment.



### Future Work

- **Implement Mutexes:** To handle shared resources between tasks more efficiently.
- **Priority Scheduling:** Extend the kernel to support different task priorities.
- **Add More Peripherals:** Integrate additional peripheral drivers (e.g., ADC, Timers) for richer RTOS features.
- **Computations** I want to see how different types of computations would fare on different types of scheduling algorithms

### License

This project is open-source and available under the MIT License. Contributions are welcome!

---

Feel free to use this as a base for your project. Let me know if you'd like any adjustments!
